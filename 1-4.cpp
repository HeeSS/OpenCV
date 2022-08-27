/* 1-4.cpp
이미지 얕은복사, 깊은복사  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat img1 = imread("puppy.bmp");
	Mat img2 = img1; //얕은복사(img2을 생성하면서 img1와 메모리 공유)
	Mat img3(img2); //얕은복사(img3을 생성하면서 img2와 메모리 공유)

	Mat img4; 
	img3.copyTo(img4); //깊은복사(create 메소드 호출)
	
	Mat img5 = img3.clone(); //깊은복사(새로운 복사본 생성)

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