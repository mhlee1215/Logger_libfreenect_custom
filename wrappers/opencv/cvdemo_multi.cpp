
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
#include <pthread.h>
#include "libfreenect_cv.h"

using namespace std;


//FILE * logFile;
FILE ** logFiles;
string logFolder;
bool isRecording;
bool isMakeSnapshot;
bool isFirstFrame;
//int recordedFrameNum;
int* recordedFrameNums;
char *outPath;
int kinectNum = 1;
bool isCompress = true;
int kinectStartIdx = 0;

bool isViewer = false;
bool* isUpsideDown = new bool(2);

//For encoding
CvMat * encodedImage;

uint16_t *depth_raw;
uint8_t *depth_raw_compressed;
std::string filename;
std::string* filenames;
bool cvtRGB2BGR = false;
bool hasTakenSnapshot = false;

boost::thread_group record_threads;

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
    int jpeg_params[] = {CV_IMWRITE_JPEG_QUALITY, 90, 0};

    if(encodedImage != 0)
    {
        cvReleaseMat(&encodedImage);
    }
   
    encodedImage = cvEncodeImage(".jpg", img, jpeg_params);
} 

void saveSnapShot(IplImage * img)
{
 

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

string getNextFilename(char* name, int index=0){
	if(name == NULL) return getNextFilename();

	std::stringstream strs;//bool isUpsideDown = false;
    strs << logFolder;
// #ifdef unix
    strs << "/";
// #else
//         strs << "\\";
// #endif
	strs << name;
	strs << "_";
	strs << index;
    strs << ".klg";
	return strs.str();
}

void signalHandler( int signum )
{
	record_threads.join_all();
	for(int i = 0 ; i < kinectNum ; i++){
		fseek(logFiles[i], 0, SEEK_SET);
		fwrite(&recordedFrameNums[i], sizeof(int32_t), 1, logFiles[i]);

		fflush(logFiles[i]);
		fclose(logFiles[i]);

		std::cout << "Writing " << recordedFrameNums[i] << " frames finished.\n";
	}


	// cleanup and close up stuff here  
    // terminate program  

   exit(signum);  

}

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int record(){
	//int ki = (int)(intptr_t)param;
	int fcnt = 0;
	clock_t begin_time = std::clock();

	int depth_compress_buf_size = 640 * 480 * sizeof(int16_t) * 4;
	depth_raw_compressed = (uint8_t*)malloc(depth_compress_buf_size);
	
	while (cvWaitKey(10) < 0) {
		for(int ki = 0 ; ki < kinectNum ; ki++)
		{
			int curDeviceId = ki+kinectStartIdx;
			IplImage *image = freenect_sync_get_rgb_cv(curDeviceId);
			
			if (!image) {
				std::cout << "Error: Kinect not connected?" << std::endl;
				return -1;
			}
			
			if(cvtRGB2BGR)
				cvCvtColor(image, image, CV_RGB2BGR);


			IplImage *depth = freenect_sync_get_depth_cv(curDeviceId);
			if (!depth) {
				printf("Error: Kinect not connected?\n");
				return -1;
			}

			if(isFirstFrame){
				std::cout << "RGB&DEPTH Retriving started.." << std::endl;		
			}

			//std::cout <<"hi22" << std::endl;

			isFirstFrame = false;

			if(isUpsideDown[ki]){
				//do Upside Down
				cvFlip(image, image, -1);
				cvFlip(depth, depth, -1);
			}

			//depth_raw
			// uchar** dd = NULL;
			// cvGetRawData(depth, dd);

			//depth_raw = (uint16_t*)(*dd);
			
			
			if(isViewer){
				//std::cout << "show.." << std::endl;
				std::stringstream rgb_strs;
				rgb_strs << "RGB_";
				rgb_strs << ki;
				
				cvShowImage(rgb_strs.str().c_str(), image);

				std::stringstream depth_strs;
				depth_strs << "DEPTH_";
				depth_strs << ki;

				cvShowImage(depth_strs.str().c_str(), GlViewColor(depth));	
			}

					

			


			
			if(fcnt % 30 == 0){
				//fcnt = 0;
				if(ki == 0){
					double elipse = ((double)( std::clock() - begin_time )) / CLOCKS_PER_SEC;
					//std::cout << elipse << std::endl;
					std::cout << 1/(elipse/30) << std::endl;
					begin_time = std::clock();
				}

				if(recordedFrameNums[ki] == 0){
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
			


			if(isRecording){
				if(isCompress){
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
					fwrite(&timestamp, sizeof(int64_t), 1, logFiles[ki]);
					fwrite(&depthSize, sizeof(int32_t), 1, logFiles[ki]);
					fwrite(&imageSize, sizeof(int32_t), 1, logFiles[ki]);
					fwrite(depth_raw_compressed, depthSize, 1, logFiles[ki]);
					fwrite(encodedImage->data.ptr, imageSize, 1, logFiles[ki]);
				
				}else{
					unsigned long compressed_size = 640*480*2;

					// boost::thread_group threads;
			//       threads.add_thread(new boost::thread(compress2,
			//                                            depth_raw_compressed,
			//                                            &compressed_size,
			//                                            (const Bytef*)depth->imageData,
			//                                            640 * 480 * sizeof(short),
			//                                            Z_BEST_SPEED));

			//       threads.add_thread(new boost::thread(boost::bind(&encodeJpeg,
			//                                                        //this,
			//                                                        (IplImage *)image)));

			//       threads.join_all();







					int32_t depthSize = compressed_size;//compressed_size;
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
					fwrite(&timestamp, sizeof(int64_t), 1, logFiles[ki]);
					fwrite(&depthSize, sizeof(int32_t), 1, logFiles[ki]);
					fwrite(&imageSize, sizeof(int32_t), 1, logFiles[ki]);
					fwrite(depth->imageData, depthSize, 1, logFiles[ki]);
					fwrite(image->imageData, imageSize, 1, logFiles[ki]);
		
				}
				recordedFrameNums[ki]++;

			}
		}
		fcnt++;
	}
}

//Execute example
//./freenect-cvdemo-multi . 1 1 1 0 "test" 0
int main(int argc, char **argv)
{
	
	char* resultPath = NULL;
	char* homePath = NULL;
	// bool isViewer = false;
	// //bool isUpsideDown = false;
	// bool* isUpsideDown = new bool(2);
	int maxKinectNum = 2;
	
	int kinectIdx = 0;
	

	//Initaliza params
	homePath = (char*)malloc(10);
	sprintf(homePath, ".");
	isRecording = false;
	isUpsideDown[0] = false;
	isUpsideDown[1] = true;


	char * homePathIn = getCmdOption(argv, argv + argc, "-home");
    if (homePathIn)
    {
        homePath = homePathIn;
    }

	std::cout << "HOME PATH : " << homePath << std::endl;
	

	if(cmdOptionExists(argv, argv+argc, "-rgb2bgr"))
    {
		cvtRGB2BGR = true;
    }
	std::cout << "IS CONVERT RGB2BGR? : " << cvtRGB2BGR << std::endl;

	

	if(cmdOptionExists(argv, argv+argc, "-upsidedown"))
    {
		//isUpsideDown = true;
		for(int i = 0 ; i < maxKinectNum ; i++)
			isUpsideDown[i] = !isUpsideDown[i];
	}


	if(cmdOptionExists(argv, argv+argc, "-bothup"))
    {
		for(int i = 0 ; i < maxKinectNum ; i++)
			isUpsideDown[i] = false;
	}

	if(cmdOptionExists(argv, argv+argc, "-bothdown"))
    {
		for(int i = 0 ; i < maxKinectNum ; i++)
			isUpsideDown[i] = true;
	}

	std::cout << "IS UPSIDE DOWN : " << isUpsideDown[0] << ", " << isUpsideDown[1] << std::endl;

	if(cmdOptionExists(argv, argv+argc, "-viewer"))
    {
		isViewer = true;
	}

	std::cout << "IS VIEWER : " << isViewer << std::endl;



	if(cmdOptionExists(argv, argv+argc, "-recording"))
    {
		isRecording = true;
	}
	std::cout << "IS RECORDING : " << isRecording << std::endl;

	
	char * resultPathIn = getCmdOption(argv, argv + argc, "-result");
    if (resultPathIn)
    {
		resultPath = resultPathIn;
		std::cout << "RESULT PATH : " << resultPath << std::endl;
    }else{
		std::cout << "RESULT PATH : NULL "<< std::endl;
	}

	

	char * kinectNumIn = getCmdOption(argv, argv + argc, "-kinect_num");
    if (kinectNumIn)
    {
		kinectNum = atoi(kinectNumIn);
		filenames = new std::string[kinectNum];
		logFiles = new FILE*[kinectNum];
		recordedFrameNums = new int[kinectNum];

		for(int i = 0 ; i < kinectNum ; i++){
			recordedFrameNums[i] = 0;
		}
	}
	
	std::cout << "KINECT Num : " << kinectNum << std::endl;
	

	char * kinectStartIndexIn = getCmdOption(argv, argv + argc, "-kinect_start_index");
    if (kinectStartIndexIn)
    {
		kinectStartIdx = atoi(kinectStartIndexIn);
	}


	std::signal(SIGINT, signalHandler);  

	

    
    //recordedFrameNum = 0;
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

	if(isRecording){
		for(int i = 0 ; i < kinectNum ; i++){
			filenames[i] = getNextFilename(resultPath);//"myfile.klg";	

			std::cout << filenames[i] << std::endl;
			logFiles[i] = fopen(filenames[i].c_str(), "w+");

			int32_t numFrames = 0;
			fwrite(&numFrames, sizeof(int32_t), 1, logFiles[i]);	
		}
	}else{
		std::cout << "Pre-running mode (does not save at all).." << std::endl;
	}
	
	record();
	
	return 0;
}
