/* 3-1.cpp
Ư���÷�ȭ�Ұ��� ColorDetection */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	ColorDetector cdetect;
	cdetect.setTargetColor(230, 190, 130); //B, G, R Ǫ���ϴ�

	imshow("result", cdetect.process(image)); //cdetect.process(image)

	waitKey(0);
}

Mat ColorDetector::process(const Mat& image) {
	
	Mat output;
	
	//cv::absdiff ������ ȭ�ҿ� ��Į�� �� ���� �������� ���
	absdiff(image, Scalar(target), output); //Scalar()�� BGR0���� �ٲ��ش�.

	vector<Mat> images;
	split(output, images); //ä�� �и�
	output = images[0] + images[1] + images[2]; //ä�� ���ϱ�(���߷��̼� �߻�)
												//���߷��̼�: ȭ�Ұ��� 0~255�̵��� ��ȯ

	//cv::threshold(�Է¿���, �������, ��谪(0~255), �ִ�, ���ȭ ���)
	threshold(output, output, minDist, 255, THRESH_BINARY_INV); //THRESH_BINARY_INV = 1(�������)
	//THRESH_BINARY_INV ��谪���� ũ�� 0(������) �Ҵ�
	//�۰ų� ������ �ִ�(���⼭ ���) �Ҵ� - �ϴ� ����!!!

	return output;	
}
