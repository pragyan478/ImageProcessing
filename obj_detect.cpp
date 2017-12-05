#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <fstream>
#include <iostream>
#include "math.h"
#include "string.h"

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	Mat src;
	Mat hsv;
	Mat thresh;
	vector<vector<Point> > cont;
	vector<Point> sides;
	String shape;
	src = imread("/home/madhur/Downloads/shapes.jpg");
	cvtColor(src, hsv, COLOR_BGR2HSV);
	inRange(hsv, Scalar(0, 0, 50), Scalar(180, 255, 255), thresh);
	findContours(thresh, cont, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	drawContours(src, cont, -1, Scalar(0, 255, 0), 2, 8);
	for(int i=0; i < cont.size(); i++)
	{
		approxPolyDP(Mat(cont[i]), sides, 0.01*arcLength(cont[i], true), true);
		Moments m1 = moments(cont[i], true);
		double d1 = m1.m00;
		double d2 = m1.m10;
		double d3 = m1.m01;
		double x = d2/d1;
		double y = d3/d1;
		if(sides.size()==3)
		shape = "Triangle";
		else if(sides.size()==4)
		{
			Point diff1 = sides[1] - sides[0];
			Point diff2 = sides[2] - sides[1];
			double dist1 = sqrt( diff1.ddot(diff1));
			double dist2 = sqrt( diff2.ddot(diff2));
			double r = dist1/dist2;
			if(r>=0.85 && r<=1.15)
			shape = "Square";
			else
			shape = "Rectangle";
		}
		else if(sides.size()==5)
		shape = "Pentagon";
		else if(sides.size()==6)
		shape = "Hexagon";
		else if(sides.size()==7)
		shape = "Heptagon";
		else if(sides.size()==8)
		shape = "Octagon";
		else if(sides.size()==9)
		shape = "Nonagon";
		else if(sides.size()==10)
		shape = "Decagon";
		else if(sides.size()>12)
		shape = "Circle";
		else
		shape="Not Known";
		putText(src, shape, Point(x-30.0, y), FONT_HERSHEY_PLAIN, 1.0, Scalar(0,255,0), 			2.0);
		 
	  }
	namedWindow("source", WINDOW_NORMAL);
	imshow("source", src);
	/*namedWindow("hsv", WINDOW_NORMAL);
	imshow("hsv", hsv);
	namedWindow("thresholded", WINDOW_NORMAL);
	imshow("thresholded", thresh);*/
	waitKey(0);
	return 0;
}
	
