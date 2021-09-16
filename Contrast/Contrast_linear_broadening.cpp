#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include "test.h"
using namespace std;
using namespace cv;
  
  
/*对比度展宽
a = g_a/g_b;b = (g_b-g_a)/(f_b-f_a));lam = (255-g_b)/(255-g_a)
g = a*f (0<=f<f_a)
g = b*(f-f_a)+g_a    (f_a<=f<f_b)
g = lam*(f-f_b)+g_b  (f_b<=f<255)
*/
//对比度线性展宽 a_low,a_high表示原图的重要部分图像分布像素宽度，b对应的是改进后的宽度，一般b宽度大于a


string Contrast_linear_broadening(Mat pic, int a_low, int a_high, int b_low, int b_high)
{
	double a = b_low / a_low;
	double b = (b_high - b_low) / (a_high - a_low);
	double lam = (255 - b_high) / (255 - a_high);
	for (int iRow = 0; iRow < pic.cols; iRow++)
	{
		for (int iCol = 0; iCol < pic.rows; iCol++)
		{
			if (pic.ptr<uchar>(iRow)[iCol] < a_low)
			{
				pic.ptr<uchar>(iRow)[iCol] = a * pic.ptr<uchar>(iRow)[iCol];
			}
			else if (pic.ptr<uchar>(iRow)[iCol] < a_high && pic.ptr<uchar>(iRow)[iCol] >= a_low)
			{
				pic.ptr<uchar>(iRow)[iCol] = b * (pic.ptr<uchar>(iRow)[iCol]-a_low)+b_low;
			}
			else if (pic.ptr<uchar>(iRow)[iCol] < 255 && pic.ptr<uchar>(iRow)[iCol] >= a_high)
			{
				pic.ptr<uchar>(iRow)[iCol] = lam * (pic.ptr<uchar>(iRow)[iCol] - a_high) + b_high;
			}
		}
	}
	return "Finished";
}

int main()
{
	cv::Mat img = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout << Contrast_linear_broadening(img, 100, 200, 50, 230) << endl;
	cv::imshow("lena", img);
	waitKey(0);
	return 0;
}
