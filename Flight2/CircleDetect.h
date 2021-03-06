#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace cv;
using namespace std;


class CircleDetect
{
public:
	Mat img;
	Rect roi;
	Point center;
	int radius;
	float scale;
	
	KalmanFilter KF;
	Mat measurement;
	Point kfpoint;
	Point predict_pt;
	
	CircleDetect(const Size &size,float scale_in){
		img.create(size,CV_8UC1);
		scale=scale_in;
		center=Point(0,0);
		radius=0;
		roi=Rect(0,0,round(size.width/scale_in),round(size.height/scale_in));
		};
	void setImg(Mat &img_in);
	bool circleDetection();
	void drawCircle(Mat &image);
	void clear();
	void kalmanInit(); 
	void kalmanPredict();
	void drawKalman(Mat &image);
};

void CircleDetect::clear()
{
	radius=0;
	center= Point(0, 0);
}

void CircleDetect::setImg(Mat &img_in)
{
	img=img_in.clone();
}




bool CircleDetect::circleDetection()
{
	Mat img_resize;
	
	resize(img,img_resize,Size(img.cols/scale,img.rows/scale));
	
	GaussianBlur(img_resize, img_resize, Size(5, 5), 3, 3);
	
	vector<Vec3f> circles;
	HoughCircles(img_resize(roi), circles, CV_HOUGH_GRADIENT,1, 10, 100, 60, roi.width/15, roi.width/2);
	
	
	if (circles.size() >0)
	{
		radius=round(circles[0][2])*scale;
		center=Point(round(circles[0][0]+roi.x)*scale,round(circles[0][1]+roi.y)*scale);
		if (radius <20 ){
			roi.x=0;roi.y=0;
			roi.width=img_resize.cols;
			roi.height=img_resize.rows;
			clear();
		}
		roi.x=(circles[0][0]+roi.x-circles[0][2]*1.3)<0?0:(circles[0][0]+roi.x-circles[0][2]*1.3);
		roi.y=(circles[0][1]+roi.y-circles[0][2]*1.3<0)?0:(circles[0][1]+roi.y-circles[0][2]*1.3);
		roi.width=(roi.x+circles[0][2]*1.3*2>img_resize.cols)?(img_resize.cols-roi.x):circles[0][2]*1.3*2;
		roi.height=(roi.y+circles[0][2]*1.3*2>img_resize.rows)?(img_resize.rows-roi.y):circles[0][2]*1.3*2;
	}
	else
	{
		roi.x=0;roi.y=0;
		roi.width=img_resize.cols;
		roi.height=img_resize.rows;
		clear();
	}
	if(center.x|| center.y)return true;
	return false;
}

void CircleDetect::drawCircle(Mat &image)
{
	if (center.x!=0)
	{
	
		circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		
		line(image, center - Point(10, 0), center + Point(10, 0), Scalar(0, 255, 0), 3);
		line(image, center - Point(0, 10), center + Point(0, 10), Scalar(0, 255, 0), 3);
		//circle(image, center, radius, Scalar(0, 0, 255), 3, 8, 0);

	}
	string str = format("Center:(%d,%d)   Radius:%d  Delt：(%d,%d)\n", center.x, center.y, radius,center.x-320,center.y-240);
		putText(image, str, Point(10, 30), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
		

}


void CircleDetect::kalmanInit()
{
	KF.init(4, 2, 0);  
	KF.transitionMatrix = (Mat_<float>(4, 4) <<1,0,1,0,0,1,0,1,0,0,1,0,0,0,0,1);
	setIdentity(KF.measurementMatrix);//H=[1,0,0,0;0,1,0,0] 测量矩阵  

    	setIdentity(KF.processNoiseCov, Scalar::all(1e-6));//Q高斯白噪声，单位阵  
    	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-3));//R高斯白噪声，单位阵  
    	setIdentity(KF.errorCovPost, Scalar::all(1));//P后验误差估计协方差矩阵，初始化为单位阵  
    	randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));//初始化状态为随机值
   	 measurement = Mat::zeros(2, 1, CV_32F);
    	predict_pt=Point(0,0);
    	KF.predict();
}
void CircleDetect::kalmanPredict()
{
	
	measurement.at<float>(0) = (float)center.x;  
    	measurement.at<float>(1) = (float)center.y;  
    	Mat est=KF.correct(measurement);
    	kfpoint.x=est.at<float>(0);
	kfpoint.y=est.at<float>(1);
	Mat prediction = KF.predict();  
	predict_pt.x=(int)prediction.at<float>(0);
	predict_pt.y=(int)prediction.at<float>(1);
	//cout<<"Center:"<<center<<"Predict:"<<predict_pt<<"Estimation:"<<kfpoint<<endl;
}

void CircleDetect::drawKalman(Mat &image)
{
	if (kfpoint.x!=0)
	{
	
		circle(image, kfpoint, 3, Scalar(0, 255, 0), -1, 8, 0);
		
		line(image, kfpoint - Point(10, 0), kfpoint + Point(10, 0), Scalar(255, 255, 255), 2);
		line(image, kfpoint - Point(0, 10), kfpoint + Point(0, 10), Scalar(255, 255, 255), 2);
		
		
		circle(image, predict_pt, 3, Scalar(0, 255, 0), -1, 8, 0);
		
		line(image, predict_pt - Point(10, 0), predict_pt + Point(10, 0), Scalar(110, 110, 110), 2);
		line(image, predict_pt - Point(0, 10), predict_pt + Point(0, 10), Scalar(110, 110, 110), 2);
		
	}
	string str = format("Center:(%d,%d)   Radius:%d", center.x, center.y, radius);
		putText(image, str, Point(10, 50), FONT_HERSHEY_DUPLEX, 1, Scalar(0, 0, 255));
		

}



