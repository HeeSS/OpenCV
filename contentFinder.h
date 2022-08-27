#pragma once
/* contentFinder.h  
컬러 히스토그램 역투영: 물체의 모양은 무시하고 단순히 컬러 분포만으로 검출 */
#include <opencv2/opencv.hpp>
using namespace cv;

class ContentFinder {
private:
	//히스토그램 파라미터
	float  hranges[2];
	const  float* ranges[3];
	int  channels[3];

	float  threshold; //경계값 설정
	Mat  histogram; //입력 히스토그램
	SparseMat  shistogram; //only non-zero elements are stores
	bool  isSparse;

public:
	ContentFinder() : threshold(0.1f), isSparse(false) {
		ranges[0] = hranges;  ranges[1] = hranges;  ranges[2] = hranges;
	} //channels

	void setThreshold(float t) { 
		threshold = t; 
	}

	float getThreshold() {
		return  threshold; 
	}

	void setHistogram(const Mat& h) {
		isSparse = false;  
		normalize(h, histogram, 1.0);
	}

	void setHistogram(const SparseMat& h) {
		isSparse = true;  
		normalize(h, shistogram, 1.0, NORM_L2);
	}

	//역투영을 위해 지정할 것들
	Mat find(const Mat& image) {
		Mat result;
		hranges[0] = 0.0;   hranges[1] = 255.0;
		channels[0] = 0; channels[1] = 1;  channels[2] = 2;  //세 채널
		return find(image, hranges[0], hranges[1], channels);
	}

	//히스토그램에 속하는 화소 찾기
	Mat  find(const Mat& image, float minValue, float maxValue, int *channels) {
		Mat  result;
		hranges[0] = minValue;   hranges[1] = maxValue;

		if (isSparse) { //계급 수가 너무 많으면 SparseMat 클래스 사용
			for (int i = 0; i<shistogram.dims(); i++)
				this->channels[i] = channels[i];
			
			calcBackProject(&image, 1, channels, shistogram, result, ranges, 255.0);
		}
		else {
			for (int i = 0; i<histogram.dims; i++) //히스토그램 차원 = 채널목록
				this->channels[i] = channels[i];

			//확률맵 작성
			//cv::calcBackProject(&image, 한번에 영상 한개만 사용, ... , 확률값의 1을 255로 매핑) 
			calcBackProject(&image, 1, channels, histogram, result, ranges, 255.0);

		}

		//확률맵 이진화를 통한 모델 영상 검출
		//이진 영상을 얻기 위해 역투영을 경계화
		if (threshold > 0)  
			cv::threshold(result, result, 255.0*threshold, 255.0, cv::THRESH_BINARY);
		
		return  result;
	}
};

/*
<히스토그램 역투영 절차>
1. 영상 입력 후, 관심 영역 설정
2. 관심 영역의 히스토그램 작성
3. 히스토그램 정규화
4. 확률맵 작성(calcBackProject() 사용) - 확률맵 = 신뢰도 맵
5. 확률맵 이진화를 통한 모델 영상 검출
*/
