#pragma once
/* imageComparator.h  */
#include "colorHistograms.h"

class ImageComparator {
private:
	Mat refH; //���� ������׷�
	Mat inputH; //�Է¿��� ������׷�
	ColorHistogram hist; //������ ������׷�
	int  nBins; //������׷��� ���� �� ����� ���� ����
public:
	ImageComparator() :nBins(8) {}

	void setNumberOfBins(int bins) {
		nBins = bins;
	}

	//���� ������ ������׷� ���
	void setReferenceImage(const Mat& image) {
		hist.setSize(nBins);
		refH = hist.getHistogram(image);
	}

	//�� BGR ������׷��� ����� ���� ��
	double compare(const Mat& image) {
		inputH = hist.getHistogram(image);
		//return compareHist(refH, inputH, CV_COMP_INTERSECT);
		return compareHist(refH, inputH, CV_COMP_CORREL); //��ü �ȼ� �� ��% ? �ٲ���°� ? �� ǥ��
	}
};
