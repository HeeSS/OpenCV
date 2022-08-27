/* 4-1.cpp
행렬의 등간격 히스토그램
calcHist(), normalize()  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	uchar dataA[16] = {0,0,0,0,1,1,3,5,6,1,1,3,4,3,1,7};
	Mat A(4, 4, CV_8U, dataA);
	cout << "A = " << A << endl;

	/*
     A = [  0,   0,   0,   0;
            1,   1,   3,   5;
            6,   1,   1,   3;
            4,   3,   1,   7]
     */

	int histSize[] = { 4 }; //빈 개수
	float valueRange[] = { 0, 8 }; //[0, 8)
	const float* ranges[] = { valueRange }; //화소 값 범위
	int channels[] = { 0 }; //대상 채널
	int dims = 1; //1D 히스토그램
	Mat hist; //결과 히스토그램

	//calcHist(&image, 1(단일영상의 히스토그램만), 대상채널, Mat()(마스크사용X), 결과 히스토그램, ?D, 빈 개수, 화소 값 범위, 등간격 여부)
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	cout << "hist = " << hist << endl;

	 /* histSize[] = {4}
     hist = [9; // the number of [0, 1] or [0, 2)
             3; // [2, 3] or [2, 4)
             2; // [4, 5] or [4, 6)
             2] // [6, 7] or [6, 8)
     */

	Mat pdf;
	//normalize(input, output, alpha(범위), beta(범위), normType)
	normalize(hist, pdf, 1.0, 0.0, NORM_L2);
	cout << "pdf = " << pdf << endl;

	/*
    pdf= [0.90913731;
          0.30304575;
          0.20203051;
          0.20203051]
    */

	Mat hist2;
	int histSize2[] = { 8 };
	calcHist(&A, 1, channels, Mat(), hist2, dims, histSize2, ranges, true);
	cout << "hist2 = " << hist2 << endl;

	/*
     hist2 = [4; // the number of 0
              5; // 1
              0; // 2
              3; // 3
              1; // 4
              1; // 5
              1; // 6
              1] // 7
     */

	normalize(hist2, pdf, 1.0, 0.0, NORM_L2);
	cout << "pdf = " << pdf << endl;

	/*
    pdf= [0.54433107;
          0.68041384;
          0;
          0.40824831;
          0.13608277;
          0.13608277;
          0.13608277;
          0.13608277]
    */

	return;
}
