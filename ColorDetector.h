/* ColorDetector.h */
#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

class ColorDetector {
private:
	int minDist; //최소 허용 거리
	Vec3b target; //대상 컬러
	Mat result; //결과 영상
	Mat converted; //BGR2Lab(밝기, 색도(a,b))

	//두 컬러간의 거리 계산(맨해튼 거리)
	int getDistance(const Vec3b& color) const { 
		return (abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2])); //절대값abs()
	}

public:
	ColorDetector() : minDist(100), target(0, 0, 0) {} //빈 생성자 기본 파라미터 초기화
	ColorDetector(int minD) : minDist(minD), target(0, 0, 0) {} //초기화
	
	//컬러 거리 경계값 설정(양수가 아니면 0으로 설정(입력값 유효성 체크))
	void setColorDistanceThreshold(int distance) {
		if (distance < 0) distance = 0;
		minDist = distance;
	}
	int getColorDistanceThreshold() const {
		return minDist;
	}
	void setTargetColor(uchar B, uchar G, uchar R) {
		target = Vec3b(B, G, R);
	}
	void setTargetColor(Vec3b color) {
		target = color;
	}
	Vec3b getTargetColor() const {
		return target;
	}
	Mat process(const Mat& image); //cpp파일에서 구현
};