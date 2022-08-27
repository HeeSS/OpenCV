/* 2-2.cpp
 컬러 감소 함수 colorReduce */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//Mat::at() 메소드 이용
void colorReduceAt(Mat &img, int div = 64) {
	int nl = img.rows;
	int nc = img.cols * img.channels();

	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++) {
			img.at<uchar>(i, j) = img.at<uchar>(i, j) / div * div + (div / 2);
		}
	}
}

//비트별 연산 사용
void colorReduceBitmask(Mat &img, int div = 64) {
	int nl = img.rows;
	int nc = img.cols * img.channels();
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0)); //div = pow(2,n)
	uchar mask = 0xFF << n; //화소 값을 반올림 하기 위해 사용하는 마스크

	for (int i = 0; i < nl; i++) {
		uchar* data = img.ptr<uchar>(i);

		for (int j = 0; j < nc; j++) {
			*data &= mask; 
			*data++ += div >> 1;
			//div=64 이면 4가지 컬러 &11000000
			//div=16 이면 16가지 컬러 &11110000
		}
	}
}

//이터레이터 사용
void colorReduceIterator(Mat &img, int div = 64) {
	MatIterator_<Vec3b> it = img.begin<Vec3b>();
	MatIterator_<Vec3b> itend = img.end<Vec3b>();

	while (it != itend) {
		(*it)[0] = (*it)[0] / div * div + (div / 2);
		(*it)[1] = (*it)[1] / div * div + (div / 2);
		(*it)[2] = (*it)[2] / div * div + (div / 2);
		it++;
	}
}

//ptr에 의한 방법
void colorReducePtr(Mat &img, int div = 64) {
	int nl = img.rows; //행 개수
	int nc = img.cols * img.channels(); //열 개수

	for (int i = 0; i < nl; i++) {
		uchar* data = img.ptr<uchar>(i);

		for (int j = 0; j < nc; j++) {
			data[j] = data[j] / div * div + (div / 2); //외우자!!!
													   //*data = *data /div *div + div/2; data++;
													   //*data++ = *data /div *div + div/2;
		}
	}
}

void main() {
	
	Mat img = imread("boldt.jpg");
	imshow("original", img);

	int64 start; //!!!
	double duration; //!!!

	start = getTickCount(); //!!!
	colorReduceAt(img);
	duration = (getTickCount() - start) / getTickFrequency(); //!!!
	cout << "colorReduce At= " << duration << endl;
	imshow("colorReduce At", img);

	img = imread("boldt.jpg");
	start = getTickCount();
	colorReduceBitmask(img);
	duration = (getTickCount() - start) / getTickFrequency();
	cout << "colorReduce Bitmask= " << duration << endl;
	imshow("colorReduce Bitmask", img);

	img = imread("boldt.jpg");
	start = getTickCount();
	colorReduceIterator(img);
	duration = (getTickCount() - start) / getTickFrequency();
	cout << "colorReduce Iterator= " << duration << endl;
	imshow("colorReduce Iterator", img);

	img = imread("boldt.jpg");
	start = getTickCount();
	colorReducePtr(img);
	duration = (getTickCount() - start) / getTickFrequency();
	cout << "colorReduce Ptr= " << duration << endl;
	imshow("colorReduce Ptr", img);

	waitKey(0);
}
