/* 3-1.cpp
특정컬러화소검출 ColorDetection */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	ColorDetector cdetect;
	cdetect.setTargetColor(230, 190, 130); //B, G, R 푸른하늘

	imshow("result", cdetect.process(image)); //cdetect.process(image)

	waitKey(0);
}

Mat ColorDetector::process(const Mat& image) {
	
	Mat output;
	
	//cv::absdiff 영상의 화소와 스칼라 값 간의 절대차를 계산
	absdiff(image, Scalar(target), output); //Scalar()가 BGR0으로 바꿔준다.

	vector<Mat> images;
	split(output, images); //채널 분리
	output = images[0] + images[1] + images[2]; //채널 더하기(새추레이션 발생)
												//새추레이션: 화소값이 0~255이도록 변환

	//cv::threshold(입력영상, 결과영상, 경계값(0~255), 최댓값, 경계화 모드)
	threshold(output, output, minDist, 255, THRESH_BINARY_INV); //THRESH_BINARY_INV = 1(반전모드)
	//THRESH_BINARY_INV 경계값보다 크면 0(검은색) 할당
	//작거나 같으면 최댓값(여기서 흰색) 할당 - 하늘 영역!!!

	return output;	
}
