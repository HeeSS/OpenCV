/* 2-3.cpp
영상 재매핑  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat img = imread("boldt.jpg");
	imshow("original", img);

	Mat srcX(img.rows, img.cols, CV_32F); //32비트 float
	Mat srcY(img.rows, img.cols, CV_32F);
	Mat result;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			srcX.at<float>(i, j) = j + 5 * sin(i / 10.0); //X축,열방향 물결
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0); //Y축,행방향 물결
		}
	}

	remap(img, result, srcX, srcY, INTER_LINEAR); //영상 재매핑
	imshow("remap", result);

	waitKey(0);
}