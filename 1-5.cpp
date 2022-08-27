/* 1-5.cpp
Mat 구조체 살펴보기 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	//새로운 영상 생성
	Mat img1(240, 320, CV_8U, 100); 
	
	//새로운 영상을 재할당
	img1.create(200, 200, CV_8U); 

	//빨간색 영상 생성(입력 채널: BGR)
	Mat img2(240, 320, CV_8UC3, Scalar(0, 0, 255));
	//= Mat img2(Size(240, 320), CV_8UC3, Scalar(0, 0, 255));

	imshow("img1", img1);
	imshow("img1_create", img1);
	imshow("img2", img1);

	waitKey(0);
}