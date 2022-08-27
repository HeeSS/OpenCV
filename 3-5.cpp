/* 3-5.cpp
HSV 채널분리  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");
	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels); //[0]:색상(H), [1]:채도(S), [2]:명도(V)

	//각 채널 출력
	imshow("Original", image);
	imshow("Hue", channels[0]);
	imshow("Saturate", channels[1]);
	imshow("Value", channels[2]);

	//명도 값을 모두 255로 변환 후 채널 합병
	channels[2] = 255;
	merge(channels, hsv);

	Mat newImage;
	cvtColor(hsv, newImage, CV_HSV2BGR);

	imshow("newImage", newImage);
	waitKey(0);
}
