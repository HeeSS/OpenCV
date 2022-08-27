/* 1-5.cpp
Mat ����ü ���캸�� */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	//���ο� ���� ����
	Mat img1(240, 320, CV_8U, 100); 
	
	//���ο� ������ ���Ҵ�
	img1.create(200, 200, CV_8U); 

	//������ ���� ����(�Է� ä��: BGR)
	Mat img2(240, 320, CV_8UC3, Scalar(0, 0, 255));
	//= Mat img2(Size(240, 320), CV_8UC3, Scalar(0, 0, 255));

	imshow("img1", img1);
	imshow("img1_create", img1);
	imshow("img2", img1);

	waitKey(0);
}