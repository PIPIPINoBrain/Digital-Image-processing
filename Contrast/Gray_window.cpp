#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;
  

//灰级窗，灰级窗切片  切片就是乘上255
/*       0                   0<=f(i,j)<f_a
g(i,j) = beta*(f(i*j)-f_a)   f_a<=f(i,j)<f_a
         0                   f_b<=f(i,j)<255

*/ 

string Gray_window(Mat img, int f_a, int f_b) //需要调整f_a，f_b范围
{
	float beta = 255 / (f_b - f_a);
	for (int iRow = 0; iRow < img.rows; iRow++)
	{
		uchar* p = img.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < img.cols; iCol++)
		{
			if (p[iCol] < f_b && p[iCol] >= f_a)
				p[iCol] = (uchar)(beta * (int)(p[iCol]-f_a));
			else
				p[iCol] = 0;
		}
	}
	return "Finished" ;
}

int main()
{
	cv::Mat img = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout << Gray_window(img, 100, 200) << endl;
	cv::imshow("lena", img);
	waitKey(0);
	return 0;
}
