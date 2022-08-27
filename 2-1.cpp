/* 2-1.cpp
ȭ�Ұ��� ����  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <random> //ǥ�� C++ ���� ���̺귯�� - �յ� ���� ������

using namespace cv;
using namespace std;

void salt(Mat img, int n) {

	//c++11 ���� ������
	default_random_engine generator;
	uniform_int_distribution<int> randomRow(0, img.rows - 1); //row range
	uniform_int_distribution<int> randomCol(0, img.cols - 1); //col range

	int r, c;
	for (int k = 0; k < n; k++) {
		r = randomRow(generator); //������ ���� ��ǥ(i, j)
		c = randomCol(generator);

		if(img.type() == CV_8UC1){ //gray level
			img.at<uchar>(r, c) = 255; //Mat::at(��(y), ��(x)) Mat ����� ������ ��ҿ� ����!!!
		}
		else if (img.type() == CV_8UC3) { //color
			img.at<Vec3b>(r, c)[0] = 255; //255 : white, 0 : black
			img.at<Vec3b>(r, c)[1] = 255;
			img.at<Vec3b>(r, c)[2] = 255; //typedef Vec<uchar, 3> Vec3b;
		}
	}
}

void main() {

	Mat img = imread("boldt.jpg");
	imshow("original", img);

	salt(img, 3000); //���� �߰�
	imshow("salted", img);

	waitKey(0);
}