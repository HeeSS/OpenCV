/* 1-4.cpp
�̹��� ��������, ��������  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat img1 = imread("puppy.bmp");
	Mat img2 = img1; //��������(img2�� �����ϸ鼭 img1�� �޸� ����)
	Mat img3(img2); //��������(img3�� �����ϸ鼭 img2�� �޸� ����)

	Mat img4; 
	img3.copyTo(img4); //��������(create �޼ҵ� ȣ��)
	
	Mat img5 = img3.clone(); //��������(���ο� ���纻 ����)

	imshow("original", img1);

	flip(img1, img1, 1);
	flip(img4, img4, 0);
	
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3); 
	imshow("img4", img4); 
	imshow("img5", img5);

	waitKey(0);
}