/* 4-2.cpp
  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "histograms.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("group.jpg", 0); //그레이 채널
	imshow("Image", image);

	Histogram1D h;
	MatND histo = h.getHistogram(image);
	for (int i = 0; i < 256; i++)
		cout << "Value " << i << "=" << histo.at<float>(i) << endl;
	imshow("Histogram", h.getHistogramImage(image));

	//히스토그램의 높은 봉우리 쪽으로 증가 직전에 있는 최솟값 60에서 영상 경계화
	//배경과 전경 분리
	Mat thresholded;
	threshold(image, thresholded, 60, 255, THRESH_BINARY); //60이상이면 255로
	imshow("Binary Image", thresholded);

	//룩업 테이블을 이용한 영상 변경
	int dims[1] = { 256 };
	Mat lookup(1, dims, CV_8U);
	for (int i = 0; i < 256; i++)
		lookup.at<uchar>(i) = 255 - i;
	imshow("Negative Image", h.applyLookUp(image, lookup));

	//히스토그램 늘이기
	Mat stretched = h.stretch(image, 0.01f);
	imshow("Stretched  Image", stretched);
	imshow("Stretched  Histogram", h.getHistogramImage(stretched));

	// 히스토그램 균등화(Eualization)
	Mat  eq = h.equalize(image);
	imshow("Equalized Image", eq);
	imshow("Equalized Histogram", h.getHistogramImage(eq));

	waitKey(0);
}
