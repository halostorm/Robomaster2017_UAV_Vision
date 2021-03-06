#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace cv;
using namespace std;


class TriangleDetect {
public:
	Point center;
	vector< vector <Point> > triangle;
	TriangleDetect() {
	};
	bool triangleDetection(Mat img);
	void drawTriangle(Mat image);
	void preproc(Mat img);
	int findpoint();
	
};
bool TriangleDetect::triangleDetection(Mat img)
{
	Mat img_resize;
	Mat thres;
	
	vector< vector <Point> > Triangle_candidate;
	int minSize=20;
	int maxSize=20000;
	int param1=7;
	int param2=5;
	int k=0;
	
	if(img.type()==CV_8UC3)
		cvtColor(img,img_resize,CV_BGR2GRAY);
	else img_resize=img.clone();
	
	//imshow("img1",img_resize);
	//waitKey(0);
	adaptiveThreshold(img_resize, thres, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, param1, param2);
	//imshow("img_grey",thres);
	std::vector< cv::Vec4i > hierarchy2;
	std::vector< std::vector< cv::Point > > contours2;
	cv::Mat thres2;
	findContours(thres, contours2, hierarchy2, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	vector< Point > approxCurve;
	//cout<<contours2.size()<<endl;
	for (unsigned int i = 0; i < contours2.size(); i++) {
		if (minSize < int(contours2[i].size()) && int(contours2[i].size()) < maxSize) {
			approxPolyDP(contours2[i], approxCurve, double(contours2[i].size()) * 0.05, true);
		 	if (approxCurve.size() == 3)
			{
				float minDist = 1e10;
				float maxDist = 1e-10;
				//cout<<"flag3"<<endl;
				for (int j = 0; j < 3; j++) {
					float d = std::sqrt((float)(approxCurve[j].x - approxCurve[(j + 1) % 3].x) * (approxCurve[j].x - approxCurve[(j + 1) % 3].x) +
(approxCurve[j].y - approxCurve[(j + 1) % 3].y) * (approxCurve[j].y - approxCurve[(j + 1) % 3].y));
					if (d < minDist) minDist = d;
					if (d > maxDist) maxDist = d;
				}
				if (minDist > 10 && maxDist < 64) {
					
					//cout<<k<<endl;
					for (int j = 0; j < 3; j++)
						Triangle_candidate.push_back(approxCurve);
					k++;
				}
			}
		}
	}
	if (Triangle_candidate.size() >0)
	{
		vector< Point > triangle_1;
		for(int i=0;i<Triangle_candidate.size();i++){
			float a=sqrt((float)(Triangle_candidate[i][0].x - Triangle_candidate[i][1].x) * (Triangle_candidate[i][0].x - Triangle_candidate[i][1].x) +
(float)(Triangle_candidate[i][0].y - Triangle_candidate[i][1].y) * (Triangle_candidate[i][0].y - Triangle_candidate[i][1].y));
			float b=sqrt((float)(Triangle_candidate[i][0].x - Triangle_candidate[i][2].x) * (Triangle_candidate[i][0].x - Triangle_candidate[i][2].x) +
(float)(Triangle_candidate[i][0].y - Triangle_candidate[i][2].y) * (Triangle_candidate[i][0].y - Triangle_candidate[i][2].y));
			float c=sqrt((float)(Triangle_candidate[i][2].x - Triangle_candidate[i][1].x) * (Triangle_candidate[i][2].x - Triangle_candidate[i][1].x) +
(float)(Triangle_candidate[i][2].y - Triangle_candidate[i][1].y) * (Triangle_candidate[i][2].y - Triangle_candidate[i][1].y));
			triangle_1.clear();
			if(a>b&&a>c){
				if(fabs(b-c)*6 < b)
					if (fabs(b*b+c*c-a*a)*5 < 2*b*c){
						triangle_1.push_back(Point(Triangle_candidate[i][2].x,Triangle_candidate[i][2].y));
						triangle_1.push_back(Point(Triangle_candidate[i][0].x,Triangle_candidate[i][0].y));
						triangle_1.push_back(Point(Triangle_candidate[i][1].x,Triangle_candidate[i][1].y));
						triangle.push_back(triangle_1);
					}
			}else if(b>a&&b>c){
				if(fabs(a-c)*6 < a)
					if (fabs(b*b-c*c-a*a)*5 < 2*a*c){
						//cout<<Triangle_candidate[i][2]<<endl;
						triangle_1.push_back(Point(Triangle_candidate[i][1].x,Triangle_candidate[i][1].y));
						triangle_1.push_back(Point(Triangle_candidate[i][0].x,Triangle_candidate[i][0].y));
						triangle_1.push_back(Point(Triangle_candidate[i][2].x,Triangle_candidate[i][2].y));
						triangle.push_back(triangle_1);
					}
			}else if(c>b&&c>a){
				if(fabs(b-a)*6 < b)
					if (fabs(-b*b+c*c-a*a)*5 < 2*a*b){
						//cout<<Triangle_candidate[i][1]<<endl;
						triangle_1.push_back(Point(Triangle_candidate[i][0].x,Triangle_candidate[i][0].y));
						triangle_1.push_back(Point(Triangle_candidate[i][1].x,Triangle_candidate[i][1].y));
						triangle_1.push_back(Point(Triangle_candidate[i][2].x,Triangle_candidate[i][2].y));
						triangle.push_back(triangle_1);
					}
			}
		}
		if(k) return true;
		else return false;
	}
	else
	{
		return false;
	}
}

void TriangleDetect::drawTriangle(Mat image)
{
	if (triangle.size()!=0&&(triangle[0][0].x||triangle[0][0].y))
	{
		for(int i=0;i<triangle.size();i++){
			line(image, triangle[i][1], triangle[i][2], Scalar(0, 255, 0), 3);
			line(image, triangle[i][0], triangle[i][1], Scalar(0, 255, 0), 3);
			line(image, triangle[i][2], triangle[i][0], Scalar(0, 255, 0), 3);
		}
		line(image, center - Point(10, 0), center + Point(10, 0), Scalar(0, 255, 0), 3);
		line(image, center - Point(0, 10), center + Point(0, 10), Scalar(0, 255, 0), 3);
	}
}

int TriangleDetect::findpoint() {
	if (triangle.size() != 0 && (triangle[0][0].x || triangle[0][0].y)){
		double l=0;
		double x=0, y=0;
		for (int i = 0; i < triangle.size(); i++) {
			l += sqrt((triangle[i][1].x - triangle[i][2].x) * (triangle[i][1].x - triangle[i][2].x) + (triangle[i][1].y - triangle[i][2].y) * (triangle[i][1].y - triangle[i][2].y));
		}
		l = l / triangle.size();
		for (int i = 0; i < triangle.size(); i++) {
			double x0 = (triangle[i][1].x + triangle[i][2].x) / 2;
			double y0 = (triangle[i][1].y + triangle[i][2].y) / 2;
			x += (15 * l / 4.0)*(triangle[i][0].x - x0) / sqrt((triangle[i][0].x - x0) * (triangle[i][0].x - x0) + (triangle[i][0].y - y0) * (triangle[i][0].y - y0)) + triangle[i][0].x;
			y += (15 * l / 4.0)*(triangle[i][0].y - y0) / sqrt((triangle[i][0].x - x0) * (triangle[i][0].x - x0) + (triangle[i][0].y - y0) * (triangle[i][0].y - y0)) + triangle[i][0].y;
		}
		center.x = (int)(x / triangle.size());
		center.y = (int)(y / triangle.size());
		return 1;
	}
	else return 0;
}

void TriangleDetect::preproc(Mat img) {
	triangle.clear();
}














