/* 3-2.cpp
cv::floodFill()  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	//cv::floodFill(입력/결과영상, seedPoint, 다시그릴컬러, (Rect*)0, 색상차 하한, 색상차 상한, 옵션)
	//FLOODFILL_FIXED_RANGE: 시드 색상과 현재 색상의 차이 계산
	//FLOODFILL_MASK_ONLY: seedPoint가 mask인 경우
	floodFill(image, Point(100, 50), Scalar(255, 255, 255), (Rect*)0, Scalar(35, 35, 35), Scalar(35, 35, 35), FLOODFILL_FIXED_RANGE);

	imshow("result", image);
	waitKey(0);
}
