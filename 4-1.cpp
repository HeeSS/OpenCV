/* 4-1.cpp
����� ��� ������׷�
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

	int histSize[] = { 4 }; //�� ����
	float valueRange[] = { 0, 8 }; //[0, 8)
	const float* ranges[] = { valueRange }; //ȭ�� �� ����
	int channels[] = { 0 }; //��� ä��
	int dims = 1; //1D ������׷�
	Mat hist; //��� ������׷�

	//calcHist(&image, 1(���Ͽ����� ������׷���), ���ä��, Mat()(����ũ���X), ��� ������׷�, ?D, �� ����, ȭ�� �� ����, ��� ����)
	calcHist(&A, 1, channels, Mat(), hist, dims, histSize, ranges, true);
	cout << "hist = " << hist << endl;

	 /* histSize[] = {4}
     hist = [9; // the number of [0, 1] or [0, 2)
             3; // [2, 3] or [2, 4)
             2; // [4, 5] or [4, 6)
             2] // [6, 7] or [6, 8)
     */

	Mat pdf;
	//normalize(input, output, alpha(����), beta(����), normType)
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
