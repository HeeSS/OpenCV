/* 4-7.cpp
���п����� ����: ������ ���ȭ��?
(�� ȭ�Ұ� ���� ��� ��, �� �̿�ȭ���� ��� ���� �ε巯���� ���̳���
�̻�ġ�� �����ϰ� ���ȭ �������� �߶󳽴�.
����, ��� ȭ�� �ֺ��� ���� ��� ����� �ʿ� -> ���� ���� �̿�)  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("book.bmp", 0);
	imshow("Original", image);

//��1. ������ ��� �� ���
	Mat binaryFixed;
	threshold(image, binaryFixed, 70, 255, THRESH_BINARY);
	imshow("binaryFixed", binaryFixed);


//��2. adaptiveThreshold() ���
	int blockSize = 21; //�̿� ũ��(�ȼ�)
	int threshold = 10; //ȭ�Ҹ� (���-��� ��)�� ��

	Mat binaryAdaptive;
	//cv::adaptiveThreshold ������ ���ȭ
	//(�Է¿���, �����������, ����� ���� �ִ�, ���, ���ȭŸ��, ���ũ��, ����� ��谪)
	adaptiveThreshold(image, binaryAdaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, threshold);
	imshow("binaryAdaptive", binaryAdaptive);

//��3. ��������
	Mat binary = image.clone(); //���纻 ����
	int nl = binary.rows; 
	int nc = binary.cols;
	
	//���п��� ���
	Mat iimage;
	integral(image, iimage, CV_32S);
	
	int halfSize = blockSize / 2; //10�ȼ�
	for (int j = halfSize; j < nl - halfSize - 1; j++) { //�� ��
		uchar*  data = binary.ptr<uchar>(j);
		int* idata1 = iimage.ptr<int>(j - halfSize);
		int* idata2 = iimage.ptr<int>(j + halfSize + 1);

		for (int i = halfSize; i < nc - halfSize - 1; i++) {
			int sum = (idata2[i + halfSize + 1]
				- idata2[i - halfSize]
				- idata1[i + halfSize + 1]
				+ idata1[i - halfSize]) / (blockSize*blockSize); //����!!!

			if (data[i] < (sum - threshold))  
				data[i] = 0;
			else  
				data[i] = 255;

		}
	}
	imshow("integralAdaptive", binary);

	waitKey(0);
}
