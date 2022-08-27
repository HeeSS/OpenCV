#pragma once
/* histograms.h  */
#include <opencv2/opencv.hpp>
using namespace cv;

//�׷��̷��� ������ ������׷� ����
class Histogram1D {
private:
	int histSize[1]; //�� ����
	float hranges[2]; //�� ����
	const float* ranges[1]; //�� ������ ����Ű�� ������
	int channels[1]; //������ ä�� ��ȣ

public:
	Histogram1D() {
		histSize[0] = 256;
		hranges[0] = 0.0;
		hranges[1] = 255.0;
		ranges[0] = hranges;
		channels[0] = 0;
	}

	//1D ������׷� ���
	MatND getHistogram(const Mat& image) {
		MatND hist;
		calcHist(&image, 1, channels, Mat(), hist, 1, histSize, ranges);
		return hist;
	}

	//1D ������׷��� ����� ��, ������׷� �������� ��ȯ
	Mat getHistogramImage(const Mat& image) {
		MatND hist = getHistogram(image);
		
		double maxVal = 0, minVal = 0;
		//cv::minMaxLoc(input, minVal, maxVal, minLoc(in 2D case), maxLoc(in 2D case), mask)
		minMaxLoc(hist, &minVal, &maxVal, 0, 0); //�ּ�, �ִ� �� �� ���

		Mat histImage(histSize[0], histSize[0], CV_8U, Scalar(255)); //������׷��� ǥ���� ���簢�� ����
		int hpt = static_cast<int>(0.9*histSize[0]); //�ְ� ���̰� �� �� ������ 90%
		
		//�� �� ������ �׸���
		for (int h = 0; h < histSize[0]; h++) {
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			line(histImage, Point(h, histSize[0]), Point(h, histSize[0] - intensity), Scalar::all(0));
		}
		return histImage;
	}

	//���� ����� �����ϴ� ������̺� ����
	Mat applyLookUp(const Mat& image, const Mat& lookup) {
		Mat result(image.rows, image.cols, CV_8U);
		LUT(image, lookup, result);//cv::LUT
		return result;
	}

	//���� ��� ��� �����ϱ� ���� ������׷� ���̱�
	Mat stretch(const Mat& image, float percentile) {
		float number = image.total()*percentile; //����� ���� ȭ�� ����
		Mat hist = getHistogram(image);

		//������׷��� ���� �� ã��(���� ���� �� ��)
		int imin = 0; 
		float count;
		for (count = 0.0; imin < histSize[0]; imin++) {
			count += hist.at<float>(imin);
			if (count >= number) break;
		}

		//������׷��� ������ �� ã��(���� ���� �� ��)
		int imax = histSize[0] - 1;
		for (count = 0.0; imax >= 0; imax--) {
			count += hist.at<float>(imax);
			if (count >= number) break;
		}

		//��� ���̺� ����
		int dims[1] = { 256 };
		Mat lookup(1, dims, CV_8U);
		for (int i = 0; i < 256; i++) {
			if (i < imin) lookup.at<uchar>(i) = 0; //�ּҰ� =0, �ּҰ� ���ϴ� 0 �Ҵ�
			else if (i > imax) lookup.at<uchar>(i) = 255; //�ִ밪 =255, �ִ밪 �̻� 255
			else lookup.at<uchar>(i) = cvRound(255.0*(i - imin) / (imax - imin)); //�߰��� �ִ� �� i�� �����
		}
		Mat result;
		result = applyLookUp(image, lookup);
		return result;
	}

	//������׷� �յ�ȭ (������׷� ���̱��� ����å) - ���� ������׷��� �ִ��� ���� �����
	//�÷��� ��쿡�� ��� ���п��� �յ�ȭ�� �����ؾ� �Ѵ�.
	Mat equalize(const Mat& image) {
		Mat result;
		equalizeHist(image, result);
		return result;
	}
};
