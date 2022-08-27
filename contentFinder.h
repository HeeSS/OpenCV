#pragma once
/* contentFinder.h  
�÷� ������׷� ������: ��ü�� ����� �����ϰ� �ܼ��� �÷� ���������� ���� */
#include <opencv2/opencv.hpp>
using namespace cv;

class ContentFinder {
private:
	//������׷� �Ķ����
	float  hranges[2];
	const  float* ranges[3];
	int  channels[3];

	float  threshold; //��谪 ����
	Mat  histogram; //�Է� ������׷�
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

	//�������� ���� ������ �͵�
	Mat find(const Mat& image) {
		Mat result;
		hranges[0] = 0.0;   hranges[1] = 255.0;
		channels[0] = 0; channels[1] = 1;  channels[2] = 2;  //�� ä��
		return find(image, hranges[0], hranges[1], channels);
	}

	//������׷��� ���ϴ� ȭ�� ã��
	Mat  find(const Mat& image, float minValue, float maxValue, int *channels) {
		Mat  result;
		hranges[0] = minValue;   hranges[1] = maxValue;

		if (isSparse) { //��� ���� �ʹ� ������ SparseMat Ŭ���� ���
			for (int i = 0; i<shistogram.dims(); i++)
				this->channels[i] = channels[i];
			
			calcBackProject(&image, 1, channels, shistogram, result, ranges, 255.0);
		}
		else {
			for (int i = 0; i<histogram.dims; i++) //������׷� ���� = ä�θ��
				this->channels[i] = channels[i];

			//Ȯ���� �ۼ�
			//cv::calcBackProject(&image, �ѹ��� ���� �Ѱ��� ���, ... , Ȯ������ 1�� 255�� ����) 
			calcBackProject(&image, 1, channels, histogram, result, ranges, 255.0);

		}

		//Ȯ���� ����ȭ�� ���� �� ���� ����
		//���� ������ ��� ���� �������� ���ȭ
		if (threshold > 0)  
			cv::threshold(result, result, 255.0*threshold, 255.0, cv::THRESH_BINARY);
		
		return  result;
	}
};

/*
<������׷� ������ ����>
1. ���� �Է� ��, ���� ���� ����
2. ���� ������ ������׷� �ۼ�
3. ������׷� ����ȭ
4. Ȯ���� �ۼ�(calcBackProject() ���) - Ȯ���� = �ŷڵ� ��
5. Ȯ���� ����ȭ�� ���� �� ���� ����
*/
