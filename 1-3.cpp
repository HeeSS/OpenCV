/* 1-3.cpp
�������� �׸��� */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("puppy.bmp");

	//circle(image, �߽���ǥ, ������, �÷�(������), ����)
	circle(image, Point(155, 110), 65, 0, 3);

	//putText(image, �ؽ�Ʈ, ��ġ, Ÿ��, ��Ʈ����(2��Ŀ��), �÷�(���), ����)
	putText(image, "This is a dog.", Point(40, 200), FONT_HERSHEY_PLAIN, 2.0, 255, 2);

	imshow("image", image);

	waitKey(0);
}