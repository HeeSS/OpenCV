/* 3-3.cpp
�׷��� �˰������� ���� ����  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("boldt.jpg");

	//��� �簢�� ����(mask) - ��� �簢�� �ٱ��� �ִ� ��� ȭ�Ҹ� ������� ǥ��
	Rect Rectangle(80, 40, 300, 250);

	Mat result; //����(������ ���� 4��)
	//cv::GC_BGD: ��濡 �и��� ���ϴ� ȭ�� 0
	//cv::GC_FGD: ���濡 �и��� ���ϴ� ȭ�� 1
	//cv::GC_PR_BGD: �Ƹ��� ��濡 ���� ���� ȭ�� 2
	//cv::GC_PR_FGD: �Ƹ��� ���濡 ���� ���� ȭ�� 3

	Mat bgModel, fgModel; //��(���������� ���)

	//cv::grabCut(�Է¿���, ���Ұ��, ������������ �簢��, ��, �ݺ�Ƚ��, �簢�� ���)
	grabCut(image, result, Rectangle, bgModel, fgModel, 5, GC_INIT_WITH_RECT);

	//������ ���ɼ��� ���� ȭ�� ���
	//cv::compare(src1, src2, output, cmpop)
	compare(result, GC_PR_FGD, result, CMP_EQ); //CMP_EQ: src1=src2�� ���� ���(255), �� �ܴ� 0����!

	//��� ���� ����
	Mat foreground(image.size(), CV_8UC3, Scalar(255, 255, 255)); //��� ����� ����

	rectangle(image, Rectangle, cv::Scalar(255, 255, 255), 1); //1�ȼ� �β��� �簢�� �׸���
	imshow("rectangle", image);

	image.copyTo(foreground, result); //result�� ����ũ ���� (0�κ�(���ȭ��)�� �������� ����)
	imshow("foreground", foreground);

	waitKey(0);
}
