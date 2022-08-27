#pragma once
/* histograms.h  */
#include <opencv2/opencv.hpp>
using namespace cv;

//그레이레벨 영상의 히스토그램 생성
class Histogram1D {
private:
	int histSize[1]; //빈 개수
	float hranges[2]; //값 범위
	const float* ranges[1]; //값 범위를 가리키는 포인터
	int channels[1]; //조사할 채널 번호

public:
	Histogram1D() {
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}

	//1D 히스토그램 계산
	MatND getHistogram(const Mat& image) {
		MatND hist;
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		return hist;
	}

	//1D 히스토그램을 계산한 후, 히스토그램 영상으로 반환
	Mat getHistogramImage(const Mat& image) {
		MatND hist = getHistogram(image);
		
		double maxVal = 0, minVal = 0;
		//cv::minMaxLoc(input, minVal, maxVal, minLoc(in 2D case), maxLoc(in 2D case), mask)
		minMaxLoc(hist, &minVal, &maxVal, 0, 0); //최소, 최대 빈 값 얻기

		Mat histImage(histSize[0], histSize[0], CV_8U, Scalar(255)); //히스토그램을 표시할 정사각형 영상
		int hpt = static_cast<int>(0.9*histSize[0]); //최고 높이가 총 빈 개수의 90%
		
		//빈 당 수직선 그리기
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			line(histImage, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImage;
	}

	//영상 모습을 변경하는 룩업테이블 적용
	Mat applyLookUp(const Mat& image, const Mat& lookup) {
		Mat result(image.rows, image.cols, CV_8U);
		LUT(image, lookup, result);//cv::LUT
		return result;
	}

	//영상 명암 대비를 개선하기 위해 히스토그램 늘이기
	Mat stretch(const Mat& image, float percentile) {
		float number = image.total()*percentile; //백분위 수인 화소 개수
		Mat hist = getHistogram(image);

		//히스토그램의 왼쪽 끝 찾기(가장 낮은 명도 값)
		int imin = 0; 
		float count;
		for (count = 0.0; imin < histSize[0]; imin++) {
			count += hist.at<float>(imin);
			if (count >= number) break;
		}

		//히스토그램의 오른쪽 끝 찾기(가장 높은 명도 값)
		int imax = histSize[0] - 1;
		for (count = 0.0; imax >= 0; imax--) {
			count += hist.at<float>(imax);
			if (count >= number) break;
		}

		//룩업 테이블 생성
		int dims[1] = { 256 };
		Mat lookup(1, dims, CV_8U);
		for (int i = 0; i < 256; i++) {
			if (i < imin) lookup.at<uchar>(i) = 0; //최소값 =0, 최소값 이하는 0 할당
			else if (i > imax) lookup.at<uchar>(i) = 255; //최대값 =255, 최대값 이상 255
			else lookup.at<uchar>(i) = cvRound(255.0*(i - imin) / (imax - imin)); //중간에 있는 명도 i를 재매핑
		}
		Mat result;
		result = applyLookUp(image, lookup);
		return result;
	}

	//히스토그램 균등화 (히스토그램 늘이기의 개선책) - 영상 히스토그램을 최대한 고르게 만든다
	//컬러일 경우에는 밝기 성분에만 균등화를 수행해야 한다.
	Mat equalize(const Mat& image) {
		Mat result;
		equalizeHist(image, result);
		return result;
	}
};
