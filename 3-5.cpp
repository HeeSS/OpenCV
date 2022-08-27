/* 3-5.cpp
HSV ä�κи�  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");
	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);

	vector<Mat> channels;
	split(hsv, channels); //[0]:����(H), [1]:ä��(S), [2]:��(V)

	//�� ä�� ���
	imshow("Original", image);
	imshow("Hue", channels[0]);
	imshow("Saturate", channels[1]);
	imshow("Value", channels[2]);

	//�� ���� ��� 255�� ��ȯ �� ä�� �պ�
	channels[2] = 255;
	merge(channels, hsv);

	Mat newImage;
	cvtColor(hsv, newImage, CV_HSV2BGR);

	imshow("newImage", newImage);
	waitKey(0);
}
