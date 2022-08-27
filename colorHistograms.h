#pragma once
/* colorHistograms.h  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ColorHistogram {
private:
	int  histSize[3]; //�� ������ ũ��
	float  hranges[2]; //�� ����
	const float* ranges[3];   //�� ������ ����
	int channels[3];   //����� ä��
public:
	ColorHistogram() {
		histSize[0] = histSize[1] = histSize[2] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;  ranges[1] = hranges;  ranges[2] = hranges; //�� Ŭ������ ��� ä���� ���� ����
		channels[0] = 0; channels[1] = 1;  channels[2] = 2; //3 ä��
	}
	
	//�� ���� ����
	void setSize(int size) {
		histSize[0] = histSize[1] = histSize[2] = size;
	}

	MatND  getHistogram(const Mat &image) {//1600�� �÷��� ������׷�(256x256x256)
		MatND  hist;
		//BGR �÷� ������׷�
		hranges[0] = 0.0;   hranges[1] = 255.0;
		channels[0] = 0; channels[1] = 1;  channels[2] = 2;  //�� ä��
		calcHist(&image, 1, channels, Mat(), hist, 3, histSize, ranges);
		return  hist;
	}
	
	//BGR�� HSV�� ��ȯ �� H ������׷�
	MatND  getHueHistogram(const Mat &image) {
		MatND  hist;
		Mat hsv;
		cvtColor(image, hsv, CV_BGR2HSV);

		hranges[0] = 0.0;   hranges[1] = 180.0; //���� 0~180
		channels[0] = 0; //���� ä�� 1ä��
		calcHist(&hsv, 1, channels, Mat(), hist, 1, histSize, ranges); //1D ������׷�
		return  hist;
	}

	//BGR�� HSV�� ��ȯ �� H ������׷�- mask���!!!, ���� ä���� ���� ȭ�� ����
	MatND  getHueHistogram(const Mat &image, int minSat) {
		MatND  hist;   
		Mat hsv;
		cvtColor(image, hsv, CV_BGR2HSV);
		
		Mat mask;
		if (minSat > 0) { //���� ä���� ���� ȭ�� ����
			vector<Mat> v; 
			split(hsv, v);
			threshold(v[1], mask, minSat, 255, cv::THRESH_BINARY);
		}

		hranges[0] = 0.0;   hranges[1] = 180.0;   
		channels[0] = 0;
		cv::calcHist(&hsv, 1, channels, mask, hist, 1, histSize, ranges); //mask���!!!
		return  hist;
	}
};
