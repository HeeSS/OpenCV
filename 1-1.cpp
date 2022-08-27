/* 1-1.cpp 
������ �ҷ����� ���� �����ϱ�*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	
	Mat image; //�� ���� ����
	cout << "This image is " << image.rows << " x " << image.cols << endl; //0x0

	image = imread("puppy.bmp"); //�Է� ���� �б�
	if (image.empty()) {
		cout << "unloaded" << endl;
		return;
	}
	cout << "Loaded image is " << image.rows << " x " << image.cols << endl;
	cout << "channels: " << image.channels() << endl;
	cout << "type: " << image.type() << endl;
	cout << "depth: " << image.depth() << endl;

	namedWindow("Original Image"); //Window ����(���� ����), window�� �̸����� �ĺ�
	imshow("Original Image", image);

	//------------------------------------------------------------------------------------

	Mat flip1, flip0, flipM1;
	flip(image, flip1, 1); //�¿����(����)
	flip(image, flip0, 0); //���Ϲ���(����)
	flip(image, flipM1, -1); //�����¿����(���)
	
	imshow("flip1", flip1);
	imshow("flip0", flip0);
	imshow("flip-1", flipM1);

	//------------------------------------------------------------------------------------

	//���� ���� ���� ���
	//CV_IMWRITE_JPEG_QUALITY (0~100, default 95): JPEG���Ϸ� ����, �������� ȭ�� up, ����� down
	//CV_IMWRITE_PNG_COMPRESSION (0~9, default 3): PNG ����, �������� ����� up, ����ð� up

	//CV_IMWRITE_JPEG_QUALITY = 95(default)
	imwrite("output1.jpeg", flip1);

	//CV_IMWRITE_JPEG_QUALITY = 10
	vector<int> param_jpg;
	param_jpg.push_back(CV_IMWRITE_JPEG_QUALITY);
	param_jpg.push_back(10);
	imwrite("output2.jpeg", flip1, param_jpg);

	//------------------------------------------------------------------------------------

	image = imread("puppy.bmp", CV_LOAD_IMAGE_GRAYSCALE); //0, CV_8U(��ȣ���� ����Ʈ)
	image = imread("puppy.bmp", CV_LOAD_IMAGE_COLOR); //1 (default), CV_8UC3(ȭ�Ҵ� 3����Ʈ)
	//���ڸ� ���� ������ �ָ� ������ �����ߴ� ���� �״�� �д´�.

	waitKey(0); // 0 : Ű �Է��� ������ ��ٸ� / ��� : ms ������ �־��� �ð����� ��ٸ�
}