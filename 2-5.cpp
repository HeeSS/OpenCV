/* 2-5.cpp
영상 채널 분리  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat boldt = imread("boldt.jpg");
	Mat rain = imread("rain.jpg", 0); //gray level로 읽기

	Mat result;
	vector<Mat> planes; //3개영상(BGR)의 벡터 생성 BGR 순서 주의!!!!

	split(boldt, planes); //3채널 단일영상 -> 1채널 3개영상
	planes[2] += rain; //Red 채널에 더하기 (1=Green, 0=Blue)
	merge(planes, result); //1채널의 3개 영상 -> 3채널 단일영상

	imshow("result", result);
	waitKey(0);
}