/* 1-2.cpp
�������� �ΰ���� */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	
	//�ΰ� ���� ���1
	Mat image = imread("puppy.bmp");
	Mat logo = imread("logo.bmp");

	//Rect(������ǥ(x,y), ũ��(width, height)) - col:��:x, row:��:y ����!!
	Mat imageROI(image, Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));
	logo.copyTo(imageROI);

	imshow("logo", image);
	
	//------------------------------------------------------------------------------------

	//�ΰ� ���� ���2 - ���� ����ũ ���
	Mat image = imread("puppy.bmp");
	Mat logo = imread("logo.bmp");

	Mat imageROI(image, Rect(image.cols - logo.cols, image.rows - logo.rows, logo.cols, logo.rows));
	Mat mask = imread("logo.bmp", 0); //(�׷���)�ΰ� ����ũ�� ���
	logo.copyTo(imageROI, mask);
	
	imshow("logo_mask", image);

	waitKey(0);
}