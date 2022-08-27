/* 2-2.cpp
 �÷� ���� �Լ� colorReduce */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//Mat::at() �޼ҵ� �̿�
void colorReduceAt(Mat &img, int div = 64) {
	int nl = img.rows;
	int nc = img.cols * img.channels();

	for (int i = 0; i < nl; i++) {
		for (int j = 0; j < nc; j++) {
			img.at<uchar>(i, j) = img.at<uchar>(i, j) / div * div + (div / 2);
		}
	}
}

//��Ʈ�� ���� ���
void colorReduceBitmask(Mat &img, int div = 64) {
	int nl = img.rows;
	int nc = img.cols * img.channels();
	int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0)); //div = pow(2,n)
	uchar mask = 0xFF << n; //ȭ�� ���� �ݿø� �ϱ� ���� ����ϴ� ����ũ

	for (int i = 0; i < nl; i++) {
		uchar* data = img.ptr<uchar>(i);

		for (int j = 0; j < nc; j++) {
			*data &= mask; 
			*data++ += div >> 1;
			//div=64 �̸� 4���� �÷� &11000000
			//div=16 �̸� 16���� �÷� &11110000
		}
	}
}

//���ͷ����� ���
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

//ptr�� ���� ���
void colorReducePtr(Mat &img, int div = 64) {
	int nl = img.rows; //�� ����
	int nc = img.cols * img.channels(); //�� ����

	for (int i = 0; i < nl; i++) {
		uchar* data = img.ptr<uchar>(i);

		for (int j = 0; j < nc; j++) {
			data[j] = data[j] / div * div + (div / 2); //�ܿ���!!!
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
