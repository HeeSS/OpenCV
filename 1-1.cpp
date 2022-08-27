/* 1-1.cpp 
영상을 불러오고 띄우고 저장하기*/
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {
	
	Mat image; //빈 영상 생성
	cout << "This image is " << image.rows << " x " << image.cols << endl; //0x0

	image = imread("puppy.bmp"); //입력 영상 읽기
	if (image.empty()) {
		cout << "unloaded" << endl;
		return;
	}
	cout << "Loaded image is " << image.rows << " x " << image.cols << endl;
	cout << "channels: " << image.channels() << endl;
	cout << "type: " << image.type() << endl;
	cout << "depth: " << image.depth() << endl;

	namedWindow("Original Image"); //Window 정의(선택 사항), window를 이름으로 식별
	imshow("Original Image", image);

	//------------------------------------------------------------------------------------

	Mat flip1, flip0, flipM1;
	flip(image, flip1, 1); //좌우반전(수평)
	flip(image, flip0, 0); //상하반전(수직)
	flip(image, flipM1, -1); //상하좌우반전(모두)
	
	imshow("flip1", flip1);
	imshow("flip0", flip0);
	imshow("flip-1", flipM1);

	//------------------------------------------------------------------------------------

	//영상 저장 압축 양식
	//CV_IMWRITE_JPEG_QUALITY (0~100, default 95): JPEG파일로 저장, 높을수록 화질 up, 압축률 down
	//CV_IMWRITE_PNG_COMPRESSION (0~9, default 3): PNG 파일, 높을수록 압축률 up, 압축시간 up

	//CV_IMWRITE_JPEG_QUALITY = 95(default)
	imwrite("output1.jpeg", flip1);

	//CV_IMWRITE_JPEG_QUALITY = 10
	vector<int> param_jpg;
	param_jpg.push_back(CV_IMWRITE_JPEG_QUALITY);
	param_jpg.push_back(10);
	imwrite("output2.jpeg", flip1, param_jpg);

	//------------------------------------------------------------------------------------

	image = imread("puppy.bmp", CV_LOAD_IMAGE_GRAYSCALE); //0, CV_8U(부호없는 바이트)
	image = imread("puppy.bmp", CV_LOAD_IMAGE_COLOR); //1 (default), CV_8UC3(화소당 3바이트)
	//인자를 음수 값으로 주면 영상을 저장했던 포맷 그대로 읽는다.

	waitKey(0); // 0 : 키 입력을 무한히 기다림 / 양수 : ms 단위로 주어진 시간동안 기다림
}