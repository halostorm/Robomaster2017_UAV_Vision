//System Header
#include <iostream>
#include <string>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <fstream>
#include <semaphore.h>
#include <stdio.h>
#include <signal.h>
#include <opencv2/opencv.hpp>
#include <time.h>

//DJI Linux Application Headers
#include "LinuxSerialDevice.h"
#include "LinuxThread.h"
#include "LinuxSetup.h"
#include "LinuxCleanup.h"
#include "ReadUserConfig.h"
#include "LinuxFlight.h"
#include "LinuxWaypoint.h"
#include "LinuxCamera.h"

//DJI OSDK Library Headers
#include "DJI_API.h"

//User Library Headers
#include "CircleDetect.h"
#include "TriangleDetect.hpp"
#include "uart.h"
#include "PID.h"
#include "BaseArmorDetect.h"
#include "LedController.h"
#include "para.h"
#include "/home/ubuntu/Downloads/aruco-aruco-git/src/aruco.h"
#include "RMVideoCapture.hpp"
#include "Predictor.hpp"
#include "KFT.hpp"
#include "motor.h"

using namespace std;
using namespace DJI;
using namespace DJI::onboardSDK;

pthread_rwlock_t img_spinlock;
pthread_spinlock_t tags_spinlock;
Mat Homography;
float tagPerimeter, tagPerimeter_pre;
ofstream file("log");

int r = 0;

bool RUNNING_MODE = false;
bool SHUT_MODE = false;
bool LAND_MODE = false;
int BASEDETECT_MODE = 0;

int main(){
	VideoCapture capture("/home/ubuntu/Desktop/test.avi");
	capture.set(CAP_PROP_FRAME_HEIGHT, 480);
	capture.set(CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CAP_PROP_FPS, 30.0);
	VideoWriter writer("test.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 12.0, Size(640, 480), true);
	Mat videoPlay;
	Mat img_gray;
	CircleDetect circledect(Size(640, 480), 1);
	TriangleDetect tria;
    //namedWindow("VideoPlay", WINDOW_NORMAL);
	int count=0;
	double dx = 0, dy = 0;
	circledect.clear();
	LedController led;
	PIDctrl pidX(aPx, aIx, aDx, 0.5);
	PIDctrl pidY(aPy, aIy, aDy, 0.5);
	PIDctrl pidX2(bPx, bIx, bDx, 0.5);
	PIDctrl pidY2(bPy, bIy, bDy, 0.5);
	PointKF KF;
	KF.kalmanInit();
	//MotorSend mot;
	/*while(1){
		waitKey(3000);
		mot.move();
		//cout<<motor<<endl;
	}*/
	char device[] = "/dev/ttyS0";
	int fd = uartOpen(device);
	if (fd == -1)
		printf("device error");
	uartSet(fd);
	static unsigned char motor_flag=1;
	int i=31;
	while(1){
		waitKey(3000);
		if(i==31)
			i=32;
		else 
			i=31;	
		motor_flag = (char)i;
		//cout<<(int)motor_flag<<endl;
		uartSend(fd, &motor_flag, 1);
	}
	/*
	int t0=clock();
	int t1;
	int centerCount = 0, landCount = 0, lostcount = 0;
	while (1){
		capture >> videoPlay;
		cvtColor(videoPlay, img_gray, CV_RGB2GRAY);
		tria.preproc(img_gray);
		circledect.setImg(img_gray);
		count++;
		t1=clock()-t0;
		if (circledect.circleDetection())
		{
			dy = circledect.center.x - 320;//60
			dx = 240 - circledect.center.y;// 25
			r = circledect.radius;
			KF.kalmanPredict(dx,dy);
			dx=KF.predict_pt.x;
			dy=KF.predict_pt.y;
			pidX2.calc(dx);
			pidY2.calc(dy);
			circledect.drawCircle(videoPlay);
			count++;
			cout << " R:" << r << "  C:" << circledect.center << "  PID: " << pidX2.output << "  " << pidY2.output << "  dx: " << dx << "  dy:" << dy << " count="<< count << endl;
			lostcount=0;
			led.ledON();
			file<<t1<<","<<dx<<","<<dy<<endl;
		}
		else if(tria.triangleDetection(img_gray)&&tria.findpoint()==1)
		{
			dy = tria.center.x - 320;//60
			dx = 240 - tria.center.y;
			KF.kalmanPredict(dx,dy);
			dx=KF.predict_pt.x;
			dy=KF.predict_pt.y;
			pidX2.calc(dx);
			pidY2.calc(dy);
			tria.drawTriangle(videoPlay);
			count++;
			cout << "  PID: " << pidX2.output << "  " << pidY2.output << "  dx: " << dx << "  dy:" << dy << " count="<< count << endl;
			lostcount=0;
			led.ledON();
			file<<t1<<","<<dx<<","<<dy<<endl;
		}else{
			lostcount++;
			led.ledOFF();
			cout<<"lostcount: "<<lostcount<<endl;
		}
		writer << videoPlay;
		//file<<"+1";
		imshow("VideoPlay", videoPlay);
		if(waitKey(1)>0)break;
	}
	writer.release();
	capture.release();
	/*int fd2led;
	if(!(fd2led = open("/sys/class/gpio/gpio158/value", O_WRONLY))){cout<<"cannot open gpio"<<endl;return 0;}
	while(1){
		write(fd2led, "1", strlen("1"));
		//fd2led<<"1"<<endl;
		cout<<"led on"<<endl;
		//if(waitKey(0)>0)break;
		//write(fd2led, "0", 2);
	}*/
	
}

