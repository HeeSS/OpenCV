/* 4-6.cpp
히스토그램 비교를 이용한 유사영상 검색 - 두 영상간의 히스토그램을 비교함으로 유사도 측정  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "imageComparator.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("waves.jpg");
	imshow("Query image", image);

	ImageComparator c;
	c.setReferenceImage(image);
	
	Mat input = imread("dog.jpg");
	cout << "waves vs dog: " << c.compare(input) << endl;
	//CV_COMP_INTERSECT사용했을 때 - c.compare(input)/(image.cols*image.rows)하면 전체 픽셀 중 몇%? 바뀌었는가?를 표시
	imshow("dog image", input);

	waitKey(0);
}
