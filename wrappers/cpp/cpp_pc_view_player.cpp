/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2010 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

#include <iostream>
#include <vector>
#include <pthread.h>
#include <libfreenect.hpp>
#include <stdio.h>
#include <zlib.h>
#include <stdlib.h>
#include <cstring>

#include "jpeglib.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
///#include "JPEGLoader.h"

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

uint16_t * depth = NULL;
uint8_t * rgb = NULL;

uint16_t * depth2 = NULL;
uint8_t * rgb2 = NULL;

void getNextFrame();
void inputInit();

class Mutex
{
public:
    Mutex()
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    void lock()
    {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
    }

    class ScopedLock
    {
    public:
        ScopedLock(Mutex &mutex) : _mutex(mutex)
        {
            _mutex.lock();
        }

        ~ScopedLock()
        {
            _mutex.unlock();
        }

    private:
        Mutex &_mutex;
    };

private:
    pthread_mutex_t m_mutex;
};



static void jpegFail(j_common_ptr cinfo)
{
   //assert(false && "JPEG decoding error!");
}

static void doNothing(j_decompress_ptr)
{

}


class JPEGLoader
{
    public:
        JPEGLoader()
        {}

        void readData(unsigned char * src, const int numBytes, unsigned char * data)
        {
            jpeg_decompress_struct cinfo; // IJG JPEG codec structure

            jpeg_error_mgr errorMgr;

            errorMgr.error_exit = jpegFail;

            cinfo.err = jpeg_std_error(&errorMgr);

            jpeg_create_decompress(&cinfo);

            jpeg_source_mgr srcMgr;

            cinfo.src = &srcMgr;

            // Prepare for suspending reader
            srcMgr.init_source = doNothing;
            srcMgr.resync_to_restart = jpeg_resync_to_restart;
            srcMgr.term_source = doNothing;
            srcMgr.next_input_byte = src;
            srcMgr.bytes_in_buffer = numBytes;

            jpeg_read_header(&cinfo, TRUE);

            jpeg_calc_output_dimensions(&cinfo);

            jpeg_start_decompress(&cinfo);

            int width = cinfo.output_width;
            int height = cinfo.output_height;

            JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, width * 4, 1);

            for(; height--; data += (width * 3))
            {
                jpeg_read_scanlines(&cinfo, buffer, 1);

                unsigned char * bgr = (unsigned char *)buffer[0];
                unsigned char * rgb = (unsigned char *)data;

                for(int i = 0; i < width; i++, bgr += 3, rgb += 3)
                {
                    unsigned char t0 = bgr[0], t1 = bgr[1], t2 = bgr[2];
                    rgb[2] = t0; rgb[1] = t1; rgb[0] = t2;
                }
            }

            jpeg_finish_decompress(&cinfo);

            jpeg_destroy_decompress(&cinfo);
        }
};



class MyFreenectDevice : public Freenect::FreenectDevice
{
public:
    MyFreenectDevice(freenect_context *_ctx, int _index)
        : Freenect::FreenectDevice(_ctx, _index),
          m_buffer_video(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),
          m_buffer_depth(freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_REGISTERED).bytes / 2),
          m_new_rgb_frame(false), m_new_depth_frame(false)
    {
        setDepthFormat(FREENECT_DEPTH_REGISTERED);
    }

    // Do not call directly, even in child
    void VideoCallback(void *_rgb, uint32_t timestamp)
    {
        Mutex::ScopedLock lock(m_rgb_mutex);
        uint8_t* rgb = static_cast<uint8_t*>(_rgb);
        copy(rgb, rgb+getVideoBufferSize(), m_buffer_video.begin());
        m_new_rgb_frame = true;
    }

    // Do not call directly, even in child
    void DepthCallback(void *_depth, uint32_t timestamp)
    {
        Mutex::ScopedLock lock(m_depth_mutex);
        uint16_t* depth = static_cast<uint16_t*>(_depth);
        copy(depth, depth+getDepthBufferSize()/2, m_buffer_depth.begin());
        m_new_depth_frame = true;
    }

    bool getRGB(std::vector<uint8_t> &buffer)
    {
        Mutex::ScopedLock lock(m_rgb_mutex);
        
        if (!m_new_rgb_frame)
            return false;

        buffer.swap(m_buffer_video);
        m_new_rgb_frame = false;

        return true;
    }

    bool getDepth(std::vector<uint16_t> &buffer)
    {
        Mutex::ScopedLock lock(m_depth_mutex);
        
        if (!m_new_depth_frame)
            return false;

        buffer.swap(m_buffer_depth);
        m_new_depth_frame = false;

        return true;
    }

private:
    Mutex m_rgb_mutex;
    Mutex m_depth_mutex;
    std::vector<uint8_t> m_buffer_video;
    std::vector<uint16_t> m_buffer_depth;
    bool m_new_rgb_frame;
    bool m_new_depth_frame;
};


Freenect::Freenect freenect;
//MyFreenectDevice* device;

int window(0);                // Glut window identifier
int mx = -1, my = -1;         // Prevous mouse coordinates
float anglex = 0, angley = 0; // Panning angles
float zoom = 1;               // Zoom factor
bool color = true;            // Flag to indicate to use of color in the cloud


void DrawGLScene()
{
    // static std::vector<uint8_t> rgb(640*480*3);
    // static std::vector<uint16_t> depth(640*480);

    // device->getRGB(rgb);
    // device->getDepth(depth);

    getNextFrame();

    //cvCvtColor(rgb, rgb, CV_RGB2BGR);
    //std::cout << "hihihi" << rgb << std::endl;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPointSize(1.0f);

    glBegin(GL_POINTS);

    double xF = 526.37013657;
    double yF = 526.37013657;
    double xC = 313.68782938;
    double yC = 259.01834898;


    if (!color) glColor3ub(255, 255, 255);
    for (int i = 0; i < 480*640; ++i)
    {   
        if (color)
            glColor3ub( rgb[3*i+2],    // R
                        rgb[3*i+1],    // G
                        rgb[3*i+0] );  // B

        //float f = 595.f;
        double X = (i%640 - xC) * depth[i] / xF;
        double Y = (i/640 - yC) * depth[i] / yF;
        double Z = depth[i];

//         double T[3] = {0.11209693, 0.00332302, -0.02085505};
//         double R[3][3] = {{ 9.70925603e-01 ,  5.41718947e-02 , 2.33171351e-01},
//  { -5.28655736e-02 ,  9.98531290e-01 , -1.18530556e-02},
//  { -2.33470992e-01 , -8.18302009e-04 ,  9.72363423e-01}};
        
        double Xt = X;//R[0][0]*X+R[0][1]*Y+R[0][2]*Z+T[0];
        double Yt = Y;//R[1][0]*X+R[1][1]*Y+R[1][2]*Z+T[1];
        double Zt = Z;//R[2][0]*X+R[2][1]*Y+R[2][2]*Z+T[2];


        // Convert from image plane coordinates to world coordinates
        glVertex3f( Xt,  // X = (x - cx) * d / fx
                    Yt,  // Y = (y - cy) * d / fy
                    Zt );                            // Z = d
    }

    for (int i = 0; i < 480*640; ++i)
    {   
        if (color)
            glColor3ub( rgb2[3*i+2],    // R
                        rgb2[3*i+1],    // G
                        rgb2[3*i+0] );  // B

        //float f = 595.f;

        double X = (i%640 - xC) * depth2[i] / xF;
        double Y = (i/640 - yC) * depth2[i] / yF;
        double Z = depth2[i];

        double T[3] = {-0.7366876 , 0.11566776, 0.44207531};
        double R[3][3] = {{ 0.95014597,  0.01864217,  0.31124766},
 {-0.01701559,  0.99982369, -0.0079409 },
 {-0.31134082,  0.00224895,  0.95029566}};
        
        // double Xt = R[0][0]*X+R[0][1]*Y+R[0][2]*Z+T[0];
        // double Yt = R[1][0]*X+R[1][1]*Y+R[1][2]*Z+T[1];
        // double Zt = R[2][0]*X+R[2][1]*Y+R[2][2]*Z+T[2];

        // double Xt = X;
        // double Yt = Y;
        // double Zt = Z;
        
        double Xt = X - T[0];
        double Yt = Y - T[1];
        double Zt = Z - T[2];

        Xt = R[0][0]*Xt+R[1][0]*Yt+R[2][0]*Zt;
        Yt = R[0][1]*Xt+R[1][1]*Yt+R[2][1]*Zt;
        Zt = R[0][2]*Xt+R[1][2]*Yt+R[2][2]*Zt;

        // Xt = R[0][0]*Xt+R[0][1]*Yt+R[0][2]*Zt;
        // Yt = R[1][0]*Xt+R[1][1]*Yt+R[1][2]*Zt;
        // Zt = R[2][0]*Xt+R[2][1]*Yt+R[2][2]*Zt;

        // double Xt = R[0][0]*X+R[1][0]*Y+R[2][0]*Z;
        // double Yt = R[0][1]*X+R[1][1]*Y+R[2][1]*Z;
        // double Zt = R[0][2]*X+R[1][2]*Y+R[2][2]*Z;

        // Convert from image plane coordinates to world coordinates
        glVertex3f( Xt+900,  // X = (x - cx) * d / fx
                    Yt+0,  // Y = (y - cy) * d / fy
                    Zt+180 );                            // Z = d

        // glVertex3f( X,  // X = (x - cx) * d / fx
        //             Y,  // Y = (y - cy) * d / fy
        //             Z );                            // Z = d            
    }

    glEnd();
    
    // Draw the world coordinate frame
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 0, 0);  // X-axis
    glVertex3f(  0, 0, 0);
    glVertex3f( 50, 0, 0);
    glColor3ub(0, 255, 0);  // Y-axis
    glVertex3f(0,   0, 0);
    glVertex3f(0,  50, 0);
    glColor3ub(0, 0, 255);  // Z-axis
    glVertex3f(0, 0,   0);
    glVertex3f(0, 0,  50);
    glEnd();

    // Place the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1);
    gluLookAt( -7*anglex, -7*angley, -1000.0,
                     0.0,       0.0,  2000.0,
                     0.0,      -1.0,     0.0 );

    glutSwapBuffers();
}


void keyPressed(unsigned char key, int x, int y)
{
    switch (key)
    {
        case  'C':
        case  'c':
            color = !color;
            break;

        case  'Q':
        case  'q':
        case 0x1B:  // ESC
            glutDestroyWindow(window);
            // device->stopDepth();
            // device->stopVideo();
            exit(0);
    }
}


void mouseMoved(int x, int y)
{
    if (mx >= 0 && my >= 0)
    {
        anglex += x - mx;
        angley += y - my;
    }

    mx = x;
    my = y;
}


void mouseButtonPressed(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        switch (button)
        {
            case GLUT_LEFT_BUTTON:
                mx = x;
                my = y;
                break;

            case 3:
                zoom *= 1.2f;
                break;

            case 4:
                zoom /= 1.2f;
                break;
        }
    }
    else if (state == GLUT_UP && button == GLUT_LEFT_BUTTON)
    {
        mx = -1;
        my = -1;
    }
}


void resizeGLScene(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (float)width / height, 900.0, 11000.0);

    glMatrixMode(GL_MODELVIEW);
}


void idleGLScene()
{
    glutPostRedisplay();
}


void printInfo()
{
    std::cout << "\nAvailable Controls:"              << std::endl;
    std::cout << "==================="                << std::endl;
    std::cout << "Rotate       :   Mouse Left Button" << std::endl;
    std::cout << "Zoom         :   Mouse Wheel"       << std::endl;
    std::cout << "Toggle Color :   C"                 << std::endl;
    std::cout << "Quit         :   Q or Esc\n"        << std::endl;
}


FILE* fp = fopen("./capture/2017-11-29.02.klg", "rb");
FILE* fp2 = fopen("./capture/2017-11-29.03.klg", "rb");
int currentFrame = 0;
int32_t numFrames;
int32_t curFrames = 0;
int32_t tmp32 = fread(&numFrames,sizeof(int32_t),1,fp);



int numPixels = 480*640;
unsigned char * depthReadBuffer = new unsigned char[numPixels * 2];
unsigned char * imageReadBuffer = new unsigned char[numPixels * 3];
unsigned char * decompressionBufferDepth = new unsigned char[numPixels * 2];
unsigned char * decompressionBufferImage = new unsigned char[numPixels * 3];

unsigned char * depthReadBuffer2 = new unsigned char[numPixels * 2];
unsigned char * imageReadBuffer2 = new unsigned char[numPixels * 3];
unsigned char * decompressionBufferDepth2 = new unsigned char[numPixels * 2];
unsigned char * decompressionBufferImage2 = new unsigned char[numPixels * 3];


void getNextFrame(){
    if(curFrames == numFrames){
        inputInit();
    }

    int32_t depthSize;
    int32_t imageSize;

    int64_t timestamp;
    int64_t tmp64 = fread(&timestamp,sizeof(int64_t),1,fp);
    
    //assert(tmp);


    tmp32 = fread(&depthSize,sizeof(int32_t),1,fp);
    //assert(tmp);
    tmp32 = fread(&imageSize,sizeof(int32_t),1,fp);
    //assert(tmp);
    tmp32 = fread(depthReadBuffer,depthSize,1,fp);
    //assert(tmp);

    if(imageSize > 0)
    {
        tmp32 = fread(imageReadBuffer,imageSize,1,fp);
        //assert(tmp);
    }

    if(depthSize == numPixels * 2)
    {
        memcpy(&decompressionBufferDepth[0], depthReadBuffer, numPixels * 2);
    }
    else
    {
        unsigned long decompLength = numPixels * 2;
        uncompress(&decompressionBufferDepth[0], (unsigned long *)&decompLength, (const Bytef *)depthReadBuffer, depthSize);
    }

    if(imageSize == numPixels * 3)
    {
        memcpy(&decompressionBufferImage[0], imageReadBuffer, numPixels * 3);
    }
    else if(imageSize > 0)
    {
        JPEGLoader jpeg;
        jpeg.readData(imageReadBuffer, imageSize, (unsigned char *)&decompressionBufferImage[0]);
    }
    else
    { 
        memset(&decompressionBufferImage[0], 0, numPixels * 3);
    }


    depth = (unsigned short *)decompressionBufferDepth;
    rgb = (unsigned char *)&decompressionBufferImage[0];



    tmp64 = fread(&timestamp,sizeof(int64_t),1,fp2);

    tmp32 = fread(&depthSize,sizeof(int32_t),1,fp2);
    //assert(tmp);
    tmp32 = fread(&imageSize,sizeof(int32_t),1,fp2);
    //assert(tmp);
    tmp32 = fread(depthReadBuffer2,depthSize,1,fp2);
    //assert(tmp);

    if(imageSize > 0)
    {
        tmp32 = fread(imageReadBuffer2,imageSize,1,fp2);
        //assert(tmp);
    }

    if(depthSize == numPixels * 2)
    {
        memcpy(&decompressionBufferDepth2[0], depthReadBuffer2, numPixels * 2);
    }
    else
    {
        unsigned long decompLength = numPixels * 2;
        uncompress(&decompressionBufferDepth2[0], (unsigned long *)&decompLength, (const Bytef *)depthReadBuffer2, depthSize);
    }

    if(imageSize == numPixels * 3)
    {
        memcpy(&decompressionBufferImage2[0], imageReadBuffer2, numPixels * 3);
    }
    else if(imageSize > 0)
    {
        JPEGLoader jpeg;
        jpeg.readData(imageReadBuffer2, imageSize, (unsigned char *)&decompressionBufferImage2[0]);
    }
    else
    { 
        memset(&decompressionBufferImage2[0], 0, numPixels * 3);
    }


    depth2 = (unsigned short *)decompressionBufferDepth2;
    rgb2 = (unsigned char *)&decompressionBufferImage2[0];



    //std::cout << (int)rgb[0] <<std::endl;
    //std::cout << (int)depth[0] <<std::endl;
    curFrames++;
}

void inputInit(){
    //std::cout << "load!!" << std::endl;

    // fp = fopen("./capture/2017-11-29.02.klg", "rb");
    // fp2 = fopen("./capture/2017-11-29.03.klg", "rb");

    fseek ( fp , 0 , SEEK_SET );
    fseek ( fp2 , 0 , SEEK_SET );

    //std::cout << "loaded" << std::endl;
    //int currentFrame = 0;
    //int32_t numFrames;
    int32_t tmp32 = fread(&numFrames,sizeof(int32_t),1,fp);
    std::cout << "num frame : " << numFrames << std::endl;

    tmp32 = fread(&numFrames,sizeof(int32_t),1,fp2);
    std::cout << "num frame : " << numFrames << std::endl;

    curFrames = 0;

}

int main(int argc, char **argv)
{

    
    inputInit();

    // int numPixels = 480*640;
    // unsigned char * depthReadBuffer = new unsigned char[numPixels * 2];
    // unsigned char * imageReadBuffer = new unsigned char[numPixels * 3];
    // unsigned char * decompressionBufferDepth = new unsigned char[numPixels * 2];
    // unsigned char * decompressionBufferImage = new unsigned char[numPixels * 3];

    
    //return 0;

    // device = &freenect.createDevice<MyFreenectDevice>(0);
    // device->startVideo();
    // device->startDepth();
    
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);

    window = glutCreateWindow("LibFreenect");
    glClearColor(0.45f, 0.45f, 0.45f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0, 1.0, 900.0, 11000.0);
        
    glutDisplayFunc(&DrawGLScene);
    glutIdleFunc(&idleGLScene);
    glutReshapeFunc(&resizeGLScene);
    glutKeyboardFunc(&keyPressed);
    glutMotionFunc(&mouseMoved);
    glutMouseFunc(&mouseButtonPressed);

    printInfo();

    glutMainLoop();

    return 0;
}
