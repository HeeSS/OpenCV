/* 1-3.cpp
영상위에 그리기 */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("puppy.bmp");

	//circle(image, 중심좌표, 반지름, 컬러(검은색), 굵기)
	circle(image, Point(155, 110), 65, 0, 3);

	//putText(image, 텍스트, 위치, 타입, 폰트배율(2배커짐), 컬러(흰색), 굵기)
	putText(image, "This is a dog.", Point(40, 200), FONT_HERSHEY_PLAIN, 2.0, 255, 2);

	imshow("image", image);

	waitKey(0);
}