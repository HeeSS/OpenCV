/* 3-6.cpp
검출을 위한 컬러 사용  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void detectHScolor(const Mat& image, double minHue, double maxHue, double minSat, double maxSat, Mat& mask) {
	
	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels);

	Mat mask1, mask2; 
	
	threshold(channels[0], mask1, maxHue, 255, THRESH_BINARY_INV); //maxHue 이하는 255, 이상은 0
	threshold(channels[0], mask2, minHue, 255, cv::THRESH_BINARY); //minHue 이하는 0, 이상은 255 

	Mat hueMask; //색상 마스크
	if (minHue < maxHue)
		hueMask = mask1 & mask2;
	else //간격이 0도 축과 교차하면
		hueMask = mask1 | mask2;

	threshold(channels[1], mask1, maxSat, 255, THRESH_BINARY_INV);
	threshold(channels[1], mask2, minSat, 255, THRESH_BINARY);

	Mat satMask; //채도 마스크
	satMask = mask1 & mask2;

	mask = hueMask & satMask;
}

void main() {

	Mat img = imread("girl.jpg");
	Mat mask;
	detectHScolor(img, 160, 10, 25, 166, mask);

	Mat detected(img.size(), CV_8UC3, Scalar(0, 0, 0));
	img.copyTo(detected, mask);
	
	imshow("original", img);
	imshow("detected", detected);
	waitKey(0);
}
