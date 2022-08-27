#pragma once
/* imageComparator.h  */
#include "colorHistograms.h"

class ImageComparator {
private:
	Mat refH; //기준 히스토그램
	Mat inputH; //입력영상 히스토그램
	ColorHistogram hist; //생성할 히스토그램
	int  nBins; //히스토그램을 비교할 때 사용할 빈의 개수
public:
	ImageComparator() :nBins(8) {}

	void setNumberOfBins(int bins) {
		nBins = bins;
	}

	//기준 영상의 히스토그램 계산
	void setReferenceImage(const Mat& image) {
		hist.setSize(nBins);
		refH = hist.getHistogram(image);
	}

	//두 BGR 히스토그램을 사용해 영상 비교
	double compare(const Mat& image) {
		inputH = hist.getHistogram(image);
		//return compareHist(refH, inputH, CV_COMP_INTERSECT);
		return compareHist(refH, inputH, CV_COMP_CORREL); //전체 픽셀 중 몇% ? 바뀌었는가 ? 를 표시
	}
};
