/* 4-5.cpp
��ü�� ã�� ��� �̵� �˰��� - Ȯ�� ���� ���� ��ü ��ġ�� �ݺ������� ã�Ƴ��� */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "contentFinder.h"
#include "colorHistograms.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("baboon1.jpg"); //���ؿ���
	Mat imageROI = image(Rect(110, 260, 35, 40)); //�������� ��
	rectangle(image, Rect(110, 260, 35, 40), Scalar(0, 0, 255));
	imshow("image", image);

	//imageROI ���� ������׷� ���
	int minSat = 65;
	ColorHistogram hc;
	Mat colorhist = hc.getHueHistogram(imageROI, minSat);

	ContentFinder finder;
	finder.setHistogram(colorhist); //����ȭ ������׷� ����
	finder.setThreshold(0.2f); //����ȭ

	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);
	vector<Mat> v;
	split(hsv, v);
	threshold(v[1], v[1], minSat, 255, THRESH_BINARY); //v[1] ���� ä�� ���� ���Ÿ� ���� mask
	imshow("Saturation mask", v[1]);

	image = imread("baboon3.jpg");
	cvtColor(image, hsv, CV_BGR2HSV); //HSV�� ��ȯ

	//Hue(����)������׷��� �������� ��� ���
	int ch[1] = { 0 };
	finder.setThreshold(-1.0f); //����ȭ ���� ����
	Mat result = finder.find(hsv, 0.0, 180.0, ch); 
	imshow("Backprojection of second", result);

	Rect rect(110, 260, 35, 40); //�ʱ� ������ ��ġ
	rectangle(image, rect, cv::Scalar(0, 0, 255));
	imshow("Image 2", image);

	//����̵����� ��ü Ž��
	//TermCriteria::MAX_ITER = 10, epsilon = 0.01)
	TermCriteria  criteria(TermCriteria::MAX_ITER, 10, 0.01); 
	//Ž���� ���� �ݺ�Ƚ�� ��ȯ, rect ����(����ã���ɷ�)
	cout << "meanshift= " << meanShift(result, rect, criteria) << endl; 

	rectangle(image, rect, cv::Scalar(0, 255, 0));
	imshow("Image 2 result", image);

	waitKey(0);
}

/*
<����̵� �˰��� ����>
1. �Է� ���� ���� ���� ����
2. ���ɿ����� Hue ������׷� �ۼ� - minSat�� �����Ͽ� ���� ä�� ������ ������ �� �ۼ�
3. ���ɿ��� ������׷� ����ȭ
4. �˻� ��� ���� �Է� �� HSV ��ȯ
5. �˻� ��� ���� ������
6. �˻� ��� ���� initial window ǥ��
7. meanShift stop criteria ����
8. meanShift �����Ͽ� �ִ� ���� ������ �˻�
9. �˻� ��� ������ �˻� ��� ���� ǥ��
*/