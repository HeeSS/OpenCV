/* 1-2.cpp
영상위에 로고삽입 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	
	//로고 삽입 방법1
	Mat image = imread("puppy.bmp");
	Mat logo = imread("logo.bmp");

	//Rect(시작좌표(x,y), 크기(width, height)) - col:열:x, row:행:y 주의!!
	Mat imageROI(image, Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));
	logo.copyTo(imageROI);

	imshow("logo", image);
	
	//------------------------------------------------------------------------------------

	//로고 삽입 방법2 - 영상 마스크 사용
	Mat image = imread("puppy.bmp");
	Mat logo = imread("logo.bmp");

	Mat imageROI(image, Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));
	Mat mask = imread("logo.bmp", 0); //(그레이)로고를 마스크로 사용
	logo.copyTo(imageROI, mask);
	
	imshow("logo_mask", image);

	waitKey(0);
}