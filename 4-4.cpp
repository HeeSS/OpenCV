/* 4-4.cpp
(그레이, 컬러)히스토그램 역투영  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "histograms.h"
#include "contentFinder.h"
#include "colorhistograms.h"

using namespace cv;
using namespace std;

void main() {

	//그레이 히스토그램 역투영
	Mat image = imread("waves.jpg", 0);
	Mat imageROI = image(Rect(369, 67, 25, 30)); //구름 영역

	Histogram1D h;
	Mat hist = h.getHistogram(imageROI);
	imshow("Reference Hist", h.getHistogramImage(imageROI));

	ContentFinder finder;
	finder.setHistogram(hist); //정규화 히스토그램 1차원, channels[0] = 0;
	finder.setThreshold(-1.0f); //이진화 작업 안함
	Mat result1;
	result1 = finder.find(image); //역투영맵(확률맵=신뢰도맵)

	Mat tmp; //밝음(낮은 확률), 어두움(높은 확률)로 표시해 보자
	result1.convertTo(tmp, CV_8U, -1.0, 255.0); //반전 영상 a*result+b
	imshow("BackProjection result", tmp);

	finder.setThreshold(0.12f); //Threshold =0.12*255 이진화 작업 함
	result1 = finder.find(image); //이진화 역투영 맵
	imshow("Detection Result", result1);

	rectangle(image, Rect(369, 67, 25, 30), Scalar(0, 0, 0));
	imshow("Reference", image);


	//칼라 히스토그램 역투영
	Mat  color = imread("waves.jpg");
	imageROI = color(Rect(0, 0, 100, 45)); //푸른 하늘 영역

	ColorHistogram hc;
	hc.setSize(8); //3차원 8*8*8 (채널 당 8 bins)
	Mat shist = hc.getHistogram(imageROI);

	finder.setHistogram(shist); //역투영에 사용될 정규화 히스토그램 생성
	finder.setThreshold(0.05f);
	result1 = finder.find(color); //이진화 역투영 맵
	imshow("Color Detection Result", result1);

	rectangle(color, Rect(0, 0, 100, 45), Scalar(0, 0, 0));
	imshow("Color Reference", color);

	waitKey(0);
}
