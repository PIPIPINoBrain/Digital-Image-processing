#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;
  

//线性动态范围调整 灰级窗变为 0 ，255（类似于对比度线性展宽）

string linear_dynamic_range_adjustment(Mat img, int f_a, int f_b)
{
	float beta = 255 / (f_b - f_a);
	for (int iRow = 0; iRow < img.rows; iRow++)
	{
		uchar* p = img.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < img.cols; iCol++)
		{
			if (p[iCol] < f_b && p[iCol] >= f_a)
				p[iCol] = (uchar)(beta * (int)(p[iCol] - f_a));
			else if (p[iCol] < f_a)
				p[iCol] = 0;
			else
				p[iCol] = 255;
		}
	}
	return "Finished";
}

//非线性动态范围调整（感觉和lamda增强差不多）
//g = c*log10(1+f)
string Nonlinear_dynamic_range_adjustment(Mat img, int c)
{
	for (int iRow = 0; iRow < img.rows; iRow++)
	{
		uchar* p = img.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < img.cols; iCol++)
		{
			p[iCol] = c * log10(1 + p[iCol]);
		}
	}
	return "Finished";
}

int main()
{
	cv::Mat img1 = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout << linear_dynamic_range_adjustment(img1, 100, 200) << endl;
	cv::imshow("lena1", img1);
	waitKey(0);
	cv::Mat img2 = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout << Nonlinear_dynamic_range_adjustment(img2, 30) << endl;
	cv::imshow("lena2", img2);
	waitKey(0);
	return 0;
}
