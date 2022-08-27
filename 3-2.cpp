/* 3-2.cpp
cv::floodFill()  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	//cv::floodFill(�Է�/�������, seedPoint, �ٽñ׸��÷�, (Rect*)0, ������ ����, ������ ����, �ɼ�)
	//FLOODFILL_FIXED_RANGE: �õ� ����� ���� ������ ���� ���
	//FLOODFILL_MASK_ONLY: seedPoint�� mask�� ���
	floodFill(image, Point(100, 50), Scalar(255, 255, 255), (Rect*)0, Scalar(35, 35, 35), Scalar(35, 35, 35), FLOODFILL_FIXED_RANGE);

	imshow("result", image);
	waitKey(0);
}
