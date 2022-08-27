/* 2-4.cpp
������ ���� ��� ����  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat boldt = imread("boldt.jpg");
	Mat rain = imread("rain.jpg");
	
	Mat result1;
	addWeighted(boldt, 0.7, rain, 0.9, 0, result1);

	Mat result2 = boldt * 0.7 + rain * 0.9; //result�� ������ ���

	imshow("result1", result1);
	imshow("result2", result2);

	waitKey(0);
}