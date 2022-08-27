/* 2-1.cpp
화소값에 접근  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <random> //표준 C++ 난수 라이브러리 - 균등 난수 생성기

using namespace cv;
using namespace std;

void salt(Mat img, int n) {

	//c++11 난수 생성기
	default_random_engine generator;
	uniform_int_distribution<int> randomRow(0, img.rows - 1); //row range
	uniform_int_distribution<int> randomCol(0, img.cols - 1); //col range

	int r, c;
	for (int k = 0; k < n; k++) {
		r = randomRow(generator); //무작위 영상 좌표(i, j)
		c = randomCol(generator);

		if(img.type() == CV_8UC1){ //gray level
			img.at<uchar>(r, c) = 255; //Mat::at(행(y), 열(x)) Mat 행렬의 지정된 요소에 접근!!!
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

	salt(img, 3000); //잡음 추가
	imshow("salted", img);

	waitKey(0);
}