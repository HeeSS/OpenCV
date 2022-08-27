/* 4-7.cpp
적분영상의 응용: 적응적 경계화란?
(각 화소가 지역 평균 값, 즉 이웃화소의 평균 값과 두드러지게 차이나면
이상치로 간주하고 경계화 과정에서 잘라낸다.
따라서, 모든 화소 주변의 지역 평균 계산이 필요 -> 적분 영상 이용)  */
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void main() {

	Mat image = imread("book.bmp", 0);
	imshow("Original", image);

//비교1. 고정된 경계 값 사용
	Mat binaryFixed;
	threshold(image, binaryFixed, 70, 255, THRESH_BINARY);
	imshow("binaryFixed", binaryFixed);


//비교2. adaptiveThreshold() 사용
	int blockSize = 21; //이웃 크기(픽셀)
	int threshold = 10; //화소를 (평균-경계 값)과 비교

	Mat binaryAdaptive;
	//cv::adaptiveThreshold 적응적 경계화
	//(입력영상, 결과이진영상, 결과에 대한 최댓값, 방법, 경계화타입, 블록크기, 사용할 경계값)
	adaptiveThreshold(image, binaryAdaptive, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, threshold);
	imshow("binaryAdaptive", binaryAdaptive);

//비교3. 직접구현
	Mat binary = image.clone(); //복사본 생성
	int nl = binary.rows; 
	int nc = binary.cols;
	
	//적분영상 계산
	Mat iimage;
	integral(image, iimage, CV_32S);
	
	int halfSize = blockSize / 2; //10픽셀
	for (int j = halfSize; j < nl - halfSize - 1; j++) { //각 행
		uchar*  data = binary.ptr<uchar>(j);
		int* idata1 = iimage.ptr<int>(j - halfSize);
		int* idata2 = iimage.ptr<int>(j + halfSize + 1);

		for (int i = halfSize; i < nc - halfSize - 1; i++) {
			int sum = (idata2[i + halfSize + 1]
				- idata2[i - halfSize]
				- idata1[i + halfSize + 1]
				+ idata1[i - halfSize]) / (blockSize*blockSize); //주의!!!

			if (data[i] < (sum - threshold))  
				data[i] = 0;
			else  
				data[i] = 255;

		}
	}
	imshow("integralAdaptive", binary);

	waitKey(0);
}
