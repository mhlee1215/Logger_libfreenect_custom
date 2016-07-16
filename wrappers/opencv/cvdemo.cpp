
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <zlib.h>
#include <boost/format.hpp>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::posix_time; 
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
// #include <opencv2/opencv.hpp>
// //#include <opencv/cv.h>
// //#include <opencv/highgui.h>
using namespace boost::filesystem;

#include <stdio.h>
#include <iostream>
#include <csignal>
#include <ctime>
#include "libfreenect_cv.h"

using namespace std;


FILE * logFile;
string logFolder;
bool isRecording;
bool isMakeSnapshot;
bool isFirstFrame;
int recordedFrameNum;
char *outPath;

//For encoding
CvMat * encodedImage;

uint16_t *depth_raw;
uint8_t *depth_raw_compressed;
std::string filename;
int cvtRGB2BGR = 1;
bool hasTakenSnapshot = false;

IplImage *GlViewColor(IplImage *depth)
{
	static IplImage *image = 0;
	if (!image) image = cvCreateImage(cvSize(640,480), 8, 3);
	unsigned char *depth_mid = (unsigned char*)(image->imageData);
	int i;
	for (i = 0; i < 640*480; i++) {
		int lb = ((short *)depth->imageData)[i] % 256;
		int ub = ((short *)depth->imageData)[i] / 256;
		switch (ub) {
			case 0:
				depth_mid[3*i+2] = 255;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+0] = 255-lb;
				break;
			case 1:
				depth_mid[3*i+2] = 255;
				depth_mid[3*i+1] = lb;
				depth_mid[3*i+0] = 0;
				break;
			case 2:
				depth_mid[3*i+2] = 255-lb;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+0] = 0;
				break;
			case 3:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 255;
				depth_mid[3*i+0] = lb;
				break;
			case 4:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 255-lb;
				depth_mid[3*i+0] = 255;
				break;
			case 5:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+0] = 255-lb;
				break;
			default:
				depth_mid[3*i+2] = 0;
				depth_mid[3*i+1] = 0;
				depth_mid[3*i+0] = 0;
				break;
		}
	}
	return image;
}

void encodeJpeg(IplImage * img)
{
    //cv::Mat3b rgb(480, 640, rgb_data, 1920);

    //IplImage * img = new IplImage(rgb);

    int jpeg_params[] = {CV_IMWRITE_JPEG_QUALITY, 90, 0};

    if(encodedImage != 0)
    {
        cvReleaseMat(&encodedImage);
    }
   
    encodedImage = cvEncodeImage(".jpg", img, jpeg_params);
    //CvMat stub;
    //encodedImage = cvGetMat(img, &stub, 0, 0);

    //delete img;
} 

void saveSnapShot(IplImage * img)
{
    //cv::Mat3b rgb(480, 640, rgb_data, 1920);

    //IplImage * img = new IplImage(rgb);

    //int jpeg_params[] = {CV_IMWRITE_JPEG_QUALITY, 90, 0};

    // if(encodedImage != 0)
    // {
    //     cvReleaseMat(&encodedImage);
    // }
   
    //encodedImage = cvEncodeImage(".jpg", img, jpeg_params);
    //CvMat stub;
    //encodedImage = cvGetMat(img, &stub, 0, 0);

    //delete img;


		std::stringstream strs;
        strs << logFolder;
// #ifdef unix
        strs << "/";
// #else
//         strs << "\\";
// #endif

	    strs << "rgb.jpg";
//strs << ".png";

        //cv::imwrite(strs.str().c_str(), img);

	    //if(cvtRGB2BGR==1)
		//	cvCvtColor(img,img,CV_BGR2RGB);

        cvSaveImage(strs.str().c_str(), img);
        //cv::imwrite(strs.str().c_str(), encodedImage);

        if(!hasTakenSnapshot && isRecording){
			std::stringstream strs2;
		    //strs2 << logFolder;
			// #ifdef unix
			//strs2 << "/";
			// #else
			//         strs << "\\";
			// #endif
			strs2 << filename.c_str();
		    strs2 << ".rgb.jpg";

		    std::cout << "TEST!" << strs2.str().c_str() << std::endl;
		    cvSaveImage(strs2.str().c_str(), img);

		    hasTakenSnapshot = true;
        }

   // delete img;

} 

void saveDepthSnapShot(IplImage * img)
{
    //cv::Mat4b rgb(480, 640, rgb_data, 2560);

    //IplImage * img = new IplImage(rgb);

    //int jpeg_params[] = {CV_IMWRITE_JPEG_QUALITY, 90, 0};

    // if(encodedImage != 0)
    // {
    //     cvReleaseMat(&encodedImage);
    // }
   
   // encodedImage = cvEncodeImage(".jpg", img, jpeg_params);
    //CvMat stub;
    //encodedImage = cvGetMat(img, &stub, 0, 0);

    //delete img;


		std::stringstream strs;
        strs << logFolder;
// #ifdef unix
        strs << "/";
// #else
//         strs << "\\";
// #endif
        strs << "depth.jpg";
        //strs << ".png";

        //cv::imwrite(strs.str().c_str(), img);

		//cvCvtColor(img,img,CV_BGR2RGB);
        cvSaveImage(strs.str().c_str(), img);

        
        //cv::imwrite(strs.str().c_str(), encodedImage);

   // delete img;

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

string getNextFilename(char* name){
	if(name == NULL) return getNextFilename();

	std::stringstream strs;
    strs << logFolder;
// #ifdef unix
    strs << "/";
// #else
//         strs << "\\";
// #endif
    strs << name;
    strs << ".klg";
	return strs.str();
}

void signalHandler( int signum )
{
	fseek(logFile, 0, SEEK_SET);
    fwrite(&recordedFrameNum, sizeof(int32_t), 1, logFile);

    fflush(logFile);
    fclose(logFile);

    std::cout << "Writing " << recordedFrameNum << " frames finished.\n";

    // cleanup and close up stuff here  
    // terminate program  

   exit(signum);  

}

int main(int argc, char **argv)
{
	char* resultPath = NULL;
	char* homePath = NULL;
	if( argc > 1){
		homePath = argv[1];
	}else{
		homePath = (char*)malloc(10);
		sprintf(homePath, ".");
	}

	//int cvtRGB2BGR = 1;
	if( argc > 2){
		cvtRGB2BGR = atoi(argv[2]);
	}

	int isUpsideDown = 0;
	if( argc > 3){
		isUpsideDown = atoi(argv[3]);
	}

	int isViewer = 0;
	if( argc > 4){
		isViewer = atoi(argv[4]);	
	}

	//isRecording = true;
	if( argc > 5){
		if(atoi(argv[5]) == 1)
			isRecording = true;
		else
			isRecording = false;
	}

	if( argc > 6){
		//resultPath = argv[6];

	}

	

	std::signal(SIGINT, signalHandler);  

	int fcnt = 0;
	clock_t begin_time = std::clock();

	int depth_compress_buf_size = 640 * 480 * sizeof(int16_t) * 4;
    depth_raw_compressed = (uint8_t*)malloc(depth_compress_buf_size);
    
    recordedFrameNum = 0;
    isFirstFrame = true;
    //isRecordStarted = false;

    //depth_raw = (uint16_t*)malloc(640*480*4);
    // int depth_compress_buf_size = 640 * 480 * sizeof(int16_t) * 4;
    // depth_raw_compressed = (uint8_t*)malloc(depth_compress_buf_size);


	std::cout << "Logging Started.." << std::endl;
	outPath = (char*)malloc(255);
	sprintf(outPath, homePath);
	logFolder = outPath;//+"/capture";
	logFolder.append("/capture");
	boost::filesystem::create_directory(logFolder);


	filename = getNextFilename(resultPath);//"myfile.klg";	

    if(isRecording){	
		std::cout << filename << std::endl;
		logFile = fopen(filename.c_str(), "w+");

	    int32_t numFrames = 0;
	    fwrite(&numFrames, sizeof(int32_t), 1, logFile);	
	}else{
		std::cout << "Pre-running mode.." << std::endl;
	}
	
	while (cvWaitKey(10) < 0) {
		
		IplImage *image = freenect_sync_get_rgb_cv(0);
		if (!image) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}
		
		if(cvtRGB2BGR == 1)
			cvCvtColor(image, image, CV_RGB2BGR);


		IplImage *depth = freenect_sync_get_depth_cv(0);
		if (!depth) {
		    printf("Error: Kinect not connected?\n");
		    return -1;
		}

		if(isFirstFrame){
			std::cout << "RGB&DEPTH Retriving started.." << std::endl;		
		}

		isFirstFrame = false;

		if(isUpsideDown == 1){
			//do Upside Down
			cvFlip(image, image, -1);
			cvFlip(depth, depth, -1);
		}

		//depth_raw
		// uchar** dd = NULL;
		// cvGetRawData(depth, dd);

		//depth_raw = (uint16_t*)(*dd);
		
		
		if(isViewer ==1){
			cvShowImage("RGB", image);
			cvShowImage("Depth", GlViewColor(depth));	
		}

				

		


		
		if(fcnt % 30 == 0){
			//fcnt = 0;
			double elipse = ((double)( std::clock() - begin_time )) / CLOCKS_PER_SEC;
			//std::cout << elipse << std::endl;
			std::cout << 1/(elipse/30) << std::endl;
			begin_time = std::clock();

			if(recordedFrameNum == 0){
				boost::thread_group threads;		        
	        	threads.add_thread(new boost::thread(boost::bind(&saveSnapShot,
	                                                         //this,
	                                                         (IplImage *)image)
	        												 ));
	        	threads.add_thread(new boost::thread(boost::bind(&saveDepthSnapShot,
	                                                         //this,
	                                                         (IplImage *)GlViewColor(depth))));
	        	threads.join_all();	
			}
			
		}
		fcnt++;


		if(isRecording){
			unsigned long compressed_size = 640*480*2;

			boost::thread_group threads;
	        threads.add_thread(new boost::thread(compress2,
	                                             depth_raw_compressed,
	                                             &compressed_size,
	                                             (const Bytef*)depth->imageData,
	                                             640 * 480 * sizeof(short),
	                                             Z_BEST_SPEED));

	        threads.add_thread(new boost::thread(boost::bind(&encodeJpeg,
	                                                         //this,
	                                                         (IplImage *)image)));

	        threads.join_all();







			int32_t depthSize = compressed_size;//compressed_size;
	        int32_t imageSize = encodedImage->width;

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
	        fwrite(depth_raw_compressed, depthSize, 1, logFile);
	        fwrite(encodedImage->data.ptr, imageSize, 1, logFile);

	       
			recordedFrameNum++;
			//std::cout << recordedFrameNum << std::endl;

			// boost::thread_group threads;		        
   //      	threads.add_thread(new boost::thread(boost::bind(&saveSnapShot,
   //                                                       //this,
   //                                                       (IplImage *)image),
   //      												 filename.c_str()));
   //      	threads.join_all();
		}

	}
	return 0;
}
