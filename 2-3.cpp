/* 2-3.cpp
���� �����  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat img = imread("boldt.jpg");
	imshow("original", img);

	Mat srcX(img.rows, img.cols, CV_32F); //32��Ʈ float
	Mat srcY(img.rows, img.cols, CV_32F);
	Mat result;

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			srcX.at<float>(i, j) = j + 5 * sin(i / 10.0); //X��,������ ����
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0); //Y��,����� ����
		}
	}

	remap(img, result, srcX, srcY, INTER_LINEAR); //���� �����
	imshow("remap", result);

	waitKey(0);
}