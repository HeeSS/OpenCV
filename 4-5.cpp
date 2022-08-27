/* 4-5.cpp
객체를 찾는 평균 이동 알고리즘 - 확률 맵을 통해 객체 위치를 반복적으로 찾아낸다 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include "contentFinder.h"
#include "colorHistograms.h"

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("baboon1.jpg"); //기준영상
	Mat imageROI = image(Rect(110, 260, 35, 40)); //원숭이의 얼굴
	rectangle(image, Rect(110, 260, 35, 40), Scalar(0, 0, 255));
	imshow("image", image);

	//imageROI 색상 히스토그램 얻기
	int minSat = 65;
	ColorHistogram hc;
	Mat colorhist = hc.getHueHistogram(imageROI, minSat);

	ContentFinder finder;
	finder.setHistogram(colorhist); //정규화 히스토그램 생성
	finder.setThreshold(0.2f); //이진화

	Mat hsv;
	cvtColor(image, hsv, CV_BGR2HSV);
	vector<Mat> v;
	split(hsv, v);
	threshold(v[1], v[1], minSat, 255, THRESH_BINARY); //v[1] 낮은 채도 영역 제거를 위한 mask
	imshow("Saturation mask", v[1]);

	image = imread("baboon3.jpg");
	cvtColor(image, hsv, CV_BGR2HSV); //HSV로 변환

	//Hue(색상)히스토그램의 역투영한 결과 얻기
	int ch[1] = { 0 };
	finder.setThreshold(-1.0f); //이진화 하지 않음
	Mat result = finder.find(hsv, 0.0, 180.0, ch); 
	imshow("Backprojection of second", result);

	Rect rect(110, 260, 35, 40); //초기 윈도우 위치
	rectangle(image, rect, cv::Scalar(0, 0, 255));
	imshow("Image 2", image);

	//평균이동으로 객체 탐색
	//TermCriteria::MAX_ITER = 10, epsilon = 0.01)
	TermCriteria  criteria(TermCriteria::MAX_ITER, 10, 0.01); 
	//탐색을 위한 반복횟수 반환, rect 갱신(새로찾은걸로)
	cout << "meanshift= " << meanShift(result, rect, criteria) << endl; 

	rectangle(image, rect, cv::Scalar(0, 255, 0));
	imshow("Image 2 result", image);

	waitKey(0);
}

/*
<평균이동 알고리즘 절차>
1. 입력 영상에 관심 영역 설정
2. 관심영역의 Hue 히스토그램 작성 - minSat을 설정하여 낮은 채도 영역은 제거한 후 작성
3. 관심영역 히스토그램 정규화
4. 검색 대상 영상 입력 후 HSV 변환
5. 검색 대상 영상 역투영
6. 검색 대상 영상에 initial window 표시
7. meanShift stop criteria 설정
8. meanShift 수행하여 최대 밀집 지역을 검색
9. 검색 결과 영역을 검색 대상 영상에 표시
*/