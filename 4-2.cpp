/* 4-2.cpp
  */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "histograms.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("group.jpg", 0); //�׷��� ä��
	imshow("Image", image);

	Histogram1D h;
	MatND histo = h.getHistogram(image);
	for (int i = 0; i < 256; i++)
		cout << "Value " << i << "=" << histo.at<float>(i) << endl;
	imshow("Histogram", h.getHistogramImage(image));

	//������׷��� ���� ���츮 ������ ���� ������ �ִ� �ּڰ� 60���� ���� ���ȭ
	//���� ���� �и�
	Mat thresholded;
	threshold(image, thresholded, 60, 255, THRESH_BINARY); //60�̻��̸� 255��
	imshow("Binary Image", thresholded);

	//��� ���̺��� �̿��� ���� ����
	int dims[1] = { 256 };
	Mat lookup(1, dims, CV_8U);
	for (int i = 0; i < 256; i++)
		lookup.at<uchar>(i) = 255 - i;
	imshow("Negative Image", h.applyLookUp(image, lookup));

	//������׷� ���̱�
	Mat stretched = h.stretch(image, 0.01f);
	imshow("Stretched  Image", stretched);
	imshow("Stretched  Histogram", h.getHistogramImage(stretched));

	// ������׷� �յ�ȭ(Eualization)
	Mat  eq = h.equalize(image);
	imshow("Equalized Image", eq);
	imshow("Equalized Histogram", h.getHistogramImage(eq));

	waitKey(0);
}
