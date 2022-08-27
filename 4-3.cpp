/* 4-3.cpp
OpenCV에서 히스토그램 균등화 equalizeHist(input, output)함수  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void equalizeRGB(const Mat& image, Mat& result) {
	vector<Mat> channels;

	split(image, channels);
	equalizeHist(channels[0], channels[0]);
	equalizeHist(channels[1], channels[1]);
	equalizeHist(channels[2], channels[2]);

	merge(channels, result);
}

void equalizeY(const Mat& image, Mat& result) {
	Mat tmp;
	cvtColor(image, tmp, CV_BGR2YCrCb);

	vector<Mat> channels;
	split(tmp, channels);
	equalizeHist(channels[0], channels[0]); //Y영역에만 equalize

	merge(channels, tmp);
	cvtColor(tmp, result, CV_YCrCb2BGR);	
}

void main() {

	Mat image = imread("peppers.bmp");
	Mat resultRGB, resultY;

	imshow("original", image);

	equalizeRGB(image, resultRGB);
	imshow("equalizeRGB", resultRGB);

	equalizeY(image, resultY);
	imshow("equalizeY", resultY);

	waitKey(0);
}
