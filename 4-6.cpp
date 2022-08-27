/* 4-6.cpp
������׷� �񱳸� �̿��� ���翵�� �˻� - �� ������ ������׷��� �������� ���絵 ����  */
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
	//CV_COMP_INTERSECT������� �� - c.compare(input)/(image.cols*image.rows)�ϸ� ��ü �ȼ� �� ��%? �ٲ���°�?�� ǥ��
	imshow("dog image", input);

	waitKey(0);
}
