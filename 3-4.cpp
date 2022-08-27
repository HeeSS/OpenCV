/* 3-4.cpp
 특정컬러화소검출 ColorDetection  */ //CIE L*a*b 컬러표현 이용
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	ColorDetector cdetect(50);
	cdetect.setTargetColor(230, 190, 130); //B, G, R 푸른하늘
	
	//target Color를 Lab컬러 공간으로 변환!!!
	Mat tmp(1, 1, CV_8UC3);
	tmp.at<Vec3b>(0, 0) = cdetect.getTargetColor();
	cvtColor(tmp, tmp, CV_BGR2Lab); 
	cdetect.setTargetColor(tmp.at<Vec3b>(0, 0));

	imshow("result", cdetect.process(image)); //cdetect.process(image)

	waitKey(0);
}

Mat ColorDetector::process(const Mat& image) {
	
	result.create(image.rows, image.cols, CV_8U); //1채널의 결과영상
	cvtColor(image, converted, CV_BGR2Lab);

	//변환된 영상의 반복자 얻기
	Mat_<Vec3b>::iterator it = converted.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = converted.end<Vec3b>();
	//결과 영상의 반복자 얻기
	Mat_<uchar>::iterator itout = result.begin<uchar>(); //1채널의 결과영상

	for (; it != itend; it++, itout++) { //, 주의!!!
		if (getDistance(*it) <= minDist)
			*itout = 255;
		else
			*itout = 0;
	}
	return result;
}
