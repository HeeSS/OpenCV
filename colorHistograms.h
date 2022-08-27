#pragma once
/* colorHistograms.h  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ColorHistogram {
private:
	int  histSize[3]; //각 차원의 크기
	float  hranges[2]; //값 범위
	const float* ranges[3];   //각 차원의 범위
	int channels[3];   //고려할 채널
public:
	ColorHistogram() {
		histSize[0] = histSize[1] = histSize[2] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;  ranges[1] = hranges;  ranges[2] = hranges; //이 클래스의 모든 채널은 같은 범위
		channels[0] = 0; channels[1] = 1;  channels[2] = 2; //3 채널
	}
	
	//빈 개수 설정
	void setSize(int size) {
		histSize[0] = histSize[1] = histSize[2] = size;
	}

	MatND  getHistogram(const Mat &image) {//1600만 컬러의 히스토그램(256x256x256)
		MatND  hist;
		//BGR 컬러 히스토그램
		hranges[0] = 0.0;   hranges[1] = 255.0;
		channels[0] = 0; channels[1] = 1;  channels[2] = 2;  //세 채널
		calcHist(&image, 1, channels, Mat(), hist, 3, histSize, ranges);
		return  hist;
	}
	
	//BGR을 HSV로 변환 후 H 히스토그램
	MatND  getHueHistogram(const Mat &image) {
		MatND  hist;
		Mat hsv;
		cvtColor(image, hsv, CV_BGR2HSV);

		hranges[0] = 0.0;   hranges[1] = 180.0; //범위 0~180
		channels[0] = 0; //색상 채널 1채널
		calcHist(&hsv, 1, channels, Mat(), hist, 1, histSize, ranges); //1D 히스토그램
		return  hist;
	}

	//BGR을 HSV로 변환 후 H 히스토그램- mask사용!!!, 낮은 채도를 갖는 화소 무시
	MatND  getHueHistogram(const Mat &image, int minSat) {
		MatND  hist;   
		Mat hsv;
		cvtColor(image, hsv, CV_BGR2HSV);
		
		Mat mask;
		if (minSat > 0) { //낮은 채도를 갖는 화소 무시
			vector<Mat> v; 
			split(hsv, v);
			threshold(v[1], mask, minSat, 255, cv::THRESH_BINARY);
		}

		hranges[0] = 0.0;   hranges[1] = 180.0;   
		channels[0] = 0;
		cv::calcHist(&hsv, 1, channels, mask, hist, 1, histSize, ranges); //mask사용!!!
		return  hist;
	}
};
