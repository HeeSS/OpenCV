/* 2-5.cpp
���� ä�� �и�  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat boldt = imread("boldt.jpg");
	Mat rain = imread("rain.jpg", 0); //gray level�� �б�

	Mat result;
	vector<Mat> planes; //3������(BGR)�� ���� ���� BGR ���� ����!!!!

	split(boldt, planes); //3ä�� ���Ͽ��� -> 1ä�� 3������
	planes[2] += rain; //Red ä�ο� ���ϱ� (1=Green, 0=Blue)
	merge(planes, result); //1ä���� 3�� ���� -> 3ä�� ���Ͽ���

	imshow("result", result);
	waitKey(0);
}