/* ColorDetector.h */
#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

class ColorDetector {
private:
	int minDist; //�ּ� ��� �Ÿ�
	Vec3b target; //��� �÷�
	Mat result; //��� ����
	Mat converted; //BGR2Lab(���, ����(a,b))

	//�� �÷����� �Ÿ� ���(����ư �Ÿ�)
	int getDistance(const Vec3b& color) const { 
		return (abs(color[0] - target[0]) + abs(color[1] - target[1]) + abs(color[2] - target[2])); //���밪abs()
	}

public:
	ColorDetector() : minDist(100), target(0, 0, 0) {} //�� ������ �⺻ �Ķ���� �ʱ�ȭ
	ColorDetector(int minD) : minDist(minD), target(0, 0, 0) {} //�ʱ�ȭ
	
	//�÷� �Ÿ� ��谪 ����(����� �ƴϸ� 0���� ����(�Է°� ��ȿ�� üũ))
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
	Mat process(const Mat& image); //cpp���Ͽ��� ����
};