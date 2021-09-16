#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include "test.h"
using namespace std;
using namespace cv;
  
//对比度计算  对比度高画面清晰度高，层次感强,这里选了八近邻方法
float Contrast_calculation(Mat img)
{
	int col = img.cols;
	int row = img.rows;
	cv::Mat pic(col + 2, row + 2, CV_8UC1, Scalar(0));//拓宽图像，可以当作类似padding操作
	for (int iRow = 1; iRow < row + 1; iRow++)
	{
		for (int iCol = 1; iCol < col + 1; iCol++)
		{
			pic.ptr<uchar>(iRow)[iCol] = img.ptr<uchar>(iRow - 1)[iCol - 1];
		}
	}
	imshow("sdasd", pic);
	waitKey(0);
	double Add = 0;
	int Num = 4 * 3 + 5 * 4 * 510 + 8 * ((512 * 512) - (4 * 511));
	for (int iRow = 1; iRow < row + 1; iRow++)
	{
		for (int iCol = 1; iCol < col + 1; iCol++)
		{
			double sum = (pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow - 1)[iCol - 1]), 2) + pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow - 1)[iCol]), 2) + pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow - 1)[iCol + 1]), 2) +
				pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow)[iCol - 1]), 2) + pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow)[iCol]), 2) + pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow)[iCol + 1]), 2) +
				pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow + 1)[iCol - 1]), 2) + pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow + 1)[iCol]), 2) + pow((pic.ptr<uchar>(iRow)[iCol] - pic.ptr<uchar>(iRow + 1)[iCol + 1]), 2));
			Add += sum;
		}
	}
	cout << Add / Num << endl;
	return Add / Num;
}
int main()
{
	cv::Mat img = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout<<Contrast_calculation(img)<<endl;
	return 0;
}
