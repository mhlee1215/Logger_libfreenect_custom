/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2011 individual OpenKinect contributors. See the CONTRIB file
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libfreenect.h"

#include <pthread.h>
#include <math.h>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


 #include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::posix_time; 
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
using namespace boost::filesystem;


#include <string>
#include <sstream>
#include <iostream>

using namespace std;

//#include <ft2build.h>
//#include FT_FREETYPE_H

#define MB_LEFT   0
#define MB_MIDDLE 1
#define MB_RIGHT  2



pthread_t freenect_thread;
volatile int die = 0;

int g_argc;
char **g_argv;

int window;

pthread_mutex_t gl_backbuf_mutex = PTHREAD_MUTEX_INITIALIZER;

// back: owned by libfreenect (implicit for depth)
// mid: owned by callbacks, "latest frame ready"
// front: owned by GL, "currently being drawn"
uint8_t *depth_mid, *depth_front;
uint8_t *rgb_back, *rgb_mid, *rgb_front;

GLuint gl_depth_tex;
GLuint gl_rgb_tex;

freenect_context *f_ctx;
freenect_device *f_dev;
int freenect_angle = 0;
int freenect_led;

pthread_cond_t gl_frame_cond = PTHREAD_COND_INITIALIZER;
int got_rgb = 0;
int got_depth = 0;

int frame = 0;
int my_ftime = 0;
double fps = 0;


int recordedFrameNum;
bool recordStarted;
bool isRecording;
FILE * logFile;
string logFolder;

void idle()
{
	pthread_mutex_lock(&gl_backbuf_mutex);

	// When using YUV_RGB mode, RGB frames only arrive at 15Hz, so we shouldn't force them to draw in lock-step.
	// However, this is CPU/GPU intensive when we are receiving frames in lockstep.
	while (!got_depth && !got_rgb) {
		pthread_cond_wait(&gl_frame_cond, &gl_backbuf_mutex);
	}

	if (!got_depth || !got_rgb) {
		pthread_mutex_unlock(&gl_backbuf_mutex);
		return;
	}
	pthread_mutex_unlock(&gl_backbuf_mutex);
	glutPostRedisplay();
}

void printtext(int x, int y, string String)
{
//(x,y) is from the bottom left of the window
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 1280, 0, 480, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_DEPTH_TEST);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2i(x,y);
    for (int i=0; i<String.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
    }
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


string getNextFilename()
{
    static char const* const fmt = "%Y-%m-%d";
    std::ostringstream ss;

    ss.imbue(std::locale(std::cout.getloc(), new boost::gregorian::date_facet(fmt)));
    ss << boost::gregorian::day_clock::universal_day();

    std::string dateFilename;

    // if(!lastFilename.length())
//     {
       dateFilename = ss.str();
    // }
//     else
//     {
//         dateFilename = lastFilename;
//     }

    std::string currentFile;

    int currentNum = 0;

    while(true)
    {
        std::stringstream strs;
        strs << logFolder;
// #ifdef unix
        strs << "/";
// #else
//         strs << "\\";
// #endif
        strs << dateFilename << ".";
        strs << std::setfill('0') << std::setw(2) << currentNum;
        strs << ".klg";

        if(!boost::filesystem::exists(strs.str().c_str()))
        {
            return strs.str();
        }

        currentNum++;
    }

    return "";
}
 

void DrawGLScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    
	uint8_t *tmp;

	pthread_mutex_lock(&gl_backbuf_mutex);
	if (got_depth) {
		tmp = depth_front;
		depth_front = depth_mid;
		depth_mid = tmp;
		got_depth = 0;
	}
	if (got_rgb) {
		tmp = rgb_front;
		rgb_front = rgb_mid;
		rgb_mid = tmp;
		got_rgb = 0;
	}
	
	//Record.
	if(isRecording){
		if(!recordStarted){
			//Open file and write headers

			std::string filename = getNextFilename();//"myfile.klg";
			std::cout << filename << std::endl;
			logFile = fopen(filename.c_str(), "wb+");

		    int32_t numFrames = 0;
		    fwrite(&numFrames, sizeof(int32_t), 1, logFile);

			recordStarted = true;
		}

		//Write



		int32_t depthSize = 640*480*2;//compressed_size;
        int32_t imageSize = 640*480*3;//encodedImage->width;

        /**
         * Format is:
         * int64_t: timestamp
         * int32_t: depthSize
         * int32_t: imageSize
         * depthSize * unsigned char: depth_compress_buf
         * imageSize * unsigned char: encodedImage->data.ptr
         */
        int timestamp = 1000;
        fwrite(&timestamp, sizeof(int64_t), 1, logFile);
        fwrite(&depthSize, sizeof(int32_t), 1, logFile);
        fwrite(&imageSize, sizeof(int32_t), 1, logFile);
        //fwrite(frameBuffersRaw[bufferIndex].first.first, depthSize, 1, logFile);
        fwrite(depth_front, depthSize, 1, logFile);
        fwrite(rgb_front, imageSize, 1, logFile);

       
		recordedFrameNum++;
	}else{
		if(recordStarted){
			//Closing file
			fseek(logFile, 0, SEEK_SET);
		    fwrite(&recordedFrameNum, sizeof(int32_t), 1, logFile);

		    fflush(logFile);
		    fclose(logFile);

			recordStarted = false;
		}
	}
	
	
	pthread_mutex_unlock(&gl_backbuf_mutex);

	glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 640, 480, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_front);

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(640,0,0);
	glTexCoord2f(1, 0); glVertex3f(1280,0,0);
	glTexCoord2f(1, 1); glVertex3f(1280,480,0);
	glTexCoord2f(0, 1); glVertex3f(640,480,0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, 640, 480, 0, GL_RGBA, GL_UNSIGNED_BYTE, depth_front);

	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex3f(0,0,0);
	glTexCoord2f(1, 0); glVertex3f(640,0,0);
	glTexCoord2f(1, 1); glVertex3f(640,480,0);
	glTexCoord2f(0, 1); glVertex3f(0,480,0);
	glEnd();

char string[64];
    sprintf(string, "something");
    printtext(100,100,string);

	

	glutSwapBuffers();

	frame++;
	if (frame % 30 == 0) {
		int ms = glutGet(GLUT_ELAPSED_TIME);
		fps = 30.0/((ms - my_ftime)/1000.0);
		my_ftime = ms;
	}
	
	printf("%f\n", fps);
	
	
	// glRasterPos2i(100, 120);
// 	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
// 	glutBitmapString(GLUT_BITMAP_HELVETICA_18, "text to render");
}

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q') {
		die = 1;
		pthread_join(freenect_thread, NULL);
		pthread_cond_signal(&gl_frame_cond);
		glutDestroyWindow(window);
		free(depth_mid);
		free(depth_front);
		free(rgb_back);
		free(rgb_mid);
		free(rgb_front);
		// Not pthread_exit because OSX leaves a thread lying around and doesn't exit
		exit(0);
	}
}

void onMoustButton(int button, int state, int x, int y){
	int b;
	switch(button){
		case GLUT_LEFT_BUTTON:	b=MB_LEFT; break;
		case GLUT_MIDDLE_BUTTON:	b=MB_MIDDLE; break;
		case GLUT_RIGHT_BUTTON:	b=MB_RIGHT; break;
	}
	
	
	if(GLUT_DOWN == state && b == MB_LEFT) {       
        printf("hello clicked\n");
        if(isRecording){
			printf("Record end!\n");
			isRecording = false;
		}
		else{
			printf("Record start!\n");

			logFolder = "./capture";

			recordedFrameNum = 0;
			isRecording = true;
		}
    }
    
    
	
	//if(mouse_status & MB_PRESSED(b)
	
}

void ReSizeGLScene(int Width, int Height)
{
	glViewport(0,0,Width,Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, 1280, 480, 0, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void InitGL(int Width, int Height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
    glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glShadeModel(GL_FLAT);

	glGenTextures(1, &gl_depth_tex);
	glBindTexture(GL_TEXTURE_2D, gl_depth_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &gl_rgb_tex);
	glBindTexture(GL_TEXTURE_2D, gl_rgb_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	ReSizeGLScene(Width, Height);
}

void *gl_threadfunc(void *arg)
{
	printf("GL thread\n");
	glutInit(&g_argc, g_argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1280, 480);
	glutInitWindowPosition(0, 0);

	window = glutCreateWindow("libfreenect Registration viewer 2");

	glutDisplayFunc(&DrawGLScene);
	glutIdleFunc(&idle);
	glutReshapeFunc(&ReSizeGLScene);
	glutKeyboardFunc(&keyPressed);
	glutMouseFunc(&onMoustButton);

	InitGL(1280, 480);

	glutMainLoop();

	return NULL;
}

uint16_t t_gamma[10000];

void depth_cb(freenect_device *dev, void *v_depth, uint32_t timestamp)
{
	int i;
	uint16_t *depth = (uint16_t*)v_depth;

	pthread_mutex_lock(&gl_backbuf_mutex);
	for (i=0; i<640*480; i++) {
		//if (depth[i] >= 2048) continue;
		int pval = t_gamma[depth[i]] / 4;
		int lb = pval & 0xff;
		depth_mid[4*i+3] = 128; // default alpha value
		if (depth[i] ==  0) depth_mid[4*i+3] = 0; // remove anything without depth value
		switch (pval>>8) {
			case 0:
				depth_mid[4*i+0] = 255;
				depth_mid[4*i+1] = 255-lb;
				depth_mid[4*i+2] = 255-lb;
				break;
			case 1:
				depth_mid[4*i+0] = 255;
				depth_mid[4*i+1] = lb;
				depth_mid[4*i+2] = 0;
				break;
			case 2:
				depth_mid[4*i+0] = 255-lb;
				depth_mid[4*i+1] = 255;
				depth_mid[4*i+2] = 0;
				break;
			case 3:
				depth_mid[4*i+0] = 0;
				depth_mid[4*i+1] = 255;
				depth_mid[4*i+2] = lb;
				break;
			case 4:
				depth_mid[4*i+0] = 0;
				depth_mid[4*i+1] = 255-lb;
				depth_mid[4*i+2] = 255;
				break;
			case 5:
				depth_mid[4*i+0] = 0;
				depth_mid[4*i+1] = 0;
				depth_mid[4*i+2] = 255-lb;
				break;
			default:
				depth_mid[4*i+0] = 0;
				depth_mid[4*i+1] = 0;
				depth_mid[4*i+2] = 0;
				depth_mid[4*i+3] = 0;
				break;
		}
	}
	got_depth++;
	pthread_cond_signal(&gl_frame_cond);
	pthread_mutex_unlock(&gl_backbuf_mutex);
}

void rgb_cb(freenect_device *dev, void *rgb, uint32_t timestamp)
{
	pthread_mutex_lock(&gl_backbuf_mutex);

	// swap buffers
	assert (rgb_back == rgb);
	rgb_back = rgb_mid;
	freenect_set_video_buffer(dev, rgb_back);
	rgb_mid = (uint8_t*)rgb;

	got_rgb++;
	pthread_cond_signal(&gl_frame_cond);
	pthread_mutex_unlock(&gl_backbuf_mutex);
}

void *freenect_threadfunc(void *arg)
{
	freenect_set_depth_callback(f_dev, depth_cb);
	freenect_set_video_callback(f_dev, rgb_cb);
	freenect_set_video_mode(f_dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
	freenect_set_depth_mode(f_dev, freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_REGISTERED));
	freenect_set_video_buffer(f_dev, rgb_back);

	freenect_start_depth(f_dev);
	freenect_start_video(f_dev);

	printf("'w'-tilt up, 's'-level, 'x'-tilt down, '0'-'6'-select LED mode, 'f'-video format\n");

	while (!die) {
		int res = freenect_process_events(f_ctx);
		if (res < 0 && res != -10) {
			printf("\nError %d received from libusb - aborting.\n",res);
			break;
		}
	}
	printf("\nshutting down streams...\n");

	freenect_stop_depth(f_dev);
	freenect_stop_video(f_dev);

	freenect_close_device(f_dev);
	freenect_shutdown(f_ctx);

	printf("-- done!\n");
	return NULL;
}

int main(int argc, char **argv)
{
	int res;

	depth_mid = (uint8_t*)malloc(640*480*4);
	depth_front = (uint8_t*)malloc(640*480*4);
	rgb_back = (uint8_t*)malloc(640*480*3);
	rgb_mid = (uint8_t*)malloc(640*480*3);
	rgb_front = (uint8_t*)malloc(640*480*3);

	printf("Kinect camera test\n");

	int i;
	for (i=0; i<10000; i++) {
		float v = i/2048.0;
		v = powf(v, 3)* 6;
		t_gamma[i] = v*6*256;
	}

	g_argc = argc;
	g_argv = argv;

	if (freenect_init(&f_ctx, NULL) < 0) {
		printf("freenect_init() failed\n");
		return 1;
	}

	freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
	freenect_select_subdevices(f_ctx, (freenect_device_flags)(FREENECT_DEVICE_CAMERA));

	int nr_devices = freenect_num_devices (f_ctx);
	printf ("Number of devices found: %d\n", nr_devices);

	int user_device_number = 0;
	if (argc > 1)
		user_device_number = atoi(argv[1]);

	if (nr_devices < 1) {
		freenect_shutdown(f_ctx);
		return 1;
	}

	if (freenect_open_device(f_ctx, &f_dev, user_device_number) < 0) {
		printf("Could not open device\n");
		freenect_shutdown(f_ctx);
		return 1;
	}

	res = pthread_create(&freenect_thread, NULL, freenect_threadfunc, NULL);
	if (res) {
		printf("pthread_create failed\n");
		freenect_shutdown(f_ctx);
		return 1;
	}

	// OS X requires GLUT to run on the main thread
	gl_threadfunc(NULL);

	return 0;
}
