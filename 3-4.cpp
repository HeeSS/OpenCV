/* 3-4.cpp
 Ư���÷�ȭ�Ұ��� ColorDetection  */ //CIE L*a*b �÷�ǥ�� �̿�
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	ColorDetector cdetect(50);
	cdetect.setTargetColor(230, 190, 130); //B, G, R Ǫ���ϴ�
	
	//target Color�� Lab�÷� �������� ��ȯ!!!
	Mat tmp(1, 1, CV_8UC3);
	tmp.at<Vec3b>(0, 0) = cdetect.getTargetColor();
	cvtColor(tmp, tmp, CV_BGR2Lab); 
	cdetect.setTargetColor(tmp.at<Vec3b>(0, 0));

	imshow("result", cdetect.process(image)); //cdetect.process(image)

	waitKey(0);
}

Mat ColorDetector::process(const Mat& image) {
	
	result.create(image.rows, image.cols, CV_8U); //1ä���� �������
	cvtColor(image, converted, CV_BGR2Lab);

	//��ȯ�� ������ �ݺ��� ���
	Mat_<Vec3b>::iterator it = converted.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = converted.end<Vec3b>();
	//��� ������ �ݺ��� ���
	Mat_<uchar>::iterator itout = result.begin<uchar>(); //1ä���� �������

	for (; it != itend; it++, itout++) { //, ����!!!
		if (getDistance(*it) <= minDist)
			*itout = 255;
		else
			*itout = 0;
	}
	return result;
}
