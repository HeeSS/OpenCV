/* 3-3.cpp
그랩컷 알고리즘으로 영상 분할  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	//경계 사각형 정의(mask) - 경계 사각형 바깥에 있는 모든 화소를 배경으로 표식
	Rect Rectangle(80, 40, 300, 250);

	Mat result; //분할(가능한 값은 4개)
	//cv::GC_BGD: 배경에 분명히 속하는 화소 0
	//cv::GC_FGD: 전경에 분명히 속하는 화소 1
	//cv::GC_PR_BGD: 아마도 배경에 속할 듯한 화소 2
	//cv::GC_PR_FGD: 아마도 전경에 속할 듯한 화소 3

	Mat bgModel, fgModel; //모델(내부적으로 사용)

	//cv::grabCut(입력영상, 분할결과, 전경을포함한 사각형, 모델, 반복횟수, 사각형 사용)
	grabCut(image, result, Rectangle, bgModel, fgModel, 5, GC_INIT_WITH_RECT);

	//전경일 가능성이 높은 화소 얻기
	//cv::compare(src1, src2, output, cmpop)
	compare(result, GC_PR_FGD, result, CMP_EQ); //CMP_EQ: src1=src2인 곳을 흰색(255), 그 외는 0으로!

	//결과 영상 생성
	Mat foreground(image.size(), CV_8UC3, Scalar(255, 255, 255)); //모두 흰색인 영상

	rectangle(image, Rectangle, cv::Scalar(255, 255, 255), 1); //1픽셀 두께로 사각형 그리기
	imshow("rectangle", image);

	image.copyTo(foreground, result); //result는 마스크 역할 (0부분(배경화소)는 복사하지 않음)
	imshow("foreground", foreground);

	waitKey(0);
}
