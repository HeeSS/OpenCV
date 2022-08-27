/* 4-4.cpp
(�׷���, �÷�)������׷� ������  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "histograms.h"
#include "contentFinder.h"
#include "colorhistograms.h"

using namespace cv;
using namespace std;

void main() {

	//�׷��� ������׷� ������
	Mat image = imread("waves.jpg", 0);
	Mat imageROI = image(Rect(369, 67, 25, 30)); //���� ����

	Histogram1D h;
	Mat hist = h.getHistogram(imageROI);
	imshow("Reference Hist", h.getHistogramImage(imageROI));

	ContentFinder finder;
	finder.setHistogram(hist); //����ȭ ������׷� 1����, channels[0] = 0;
	finder.setThreshold(-1.0f); //����ȭ �۾� ����
	Mat result1;
	result1 = finder.find(image); //��������(Ȯ����=�ŷڵ���)

	Mat tmp; //����(���� Ȯ��), ��ο�(���� Ȯ��)�� ǥ���� ����
	result1.convertTo(tmp, CV_8U, -1.0, 255.0); //���� ���� a*result+b
	imshow("BackProjection result", tmp);

	finder.setThreshold(0.12f); //Threshold =0.12*255 ����ȭ �۾� ��
	result1 = finder.find(image); //����ȭ ������ ��
	imshow("Detection Result", result1);

	rectangle(image, Rect(369, 67, 25, 30), Scalar(0, 0, 0));
	imshow("Reference", image);


	//Į�� ������׷� ������
	Mat  color = imread("waves.jpg");
	imageROI = color(Rect(0, 0, 100, 45)); //Ǫ�� �ϴ� ����

	ColorHistogram hc;
	hc.setSize(8); //3���� 8*8*8 (ä�� �� 8 bins)
	Mat shist = hc.getHistogram(imageROI);

	finder.setHistogram(shist); //�������� ���� ����ȭ ������׷� ����
	finder.setThreshold(0.05f);
	result1 = finder.find(color); //����ȭ ������ ��
	imshow("Color Detection Result", result1);

	rectangle(color, Rect(0, 0, 100, 45), Scalar(0, 0, 0));
	imshow("Color Reference", color);

	waitKey(0);
}
