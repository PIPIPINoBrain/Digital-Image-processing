#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
using namespace cv;
  
//Downsampling 下采样，缩小
//计算采样间隔，求出缩小图像 
//     i_ = 1/k1, j_ = 1/k2
//     g(i,j) = f(i_*i,j_*j)
//缺点：没有被选取到的点无法反映到图像上

string Downsampling(float k1, float k2, Mat pic)
{
	float i_ = 1 / k1;
	float j_ = 1 / k2;
	cout << i_ << endl;
	int row = pic.rows * k1;
	int col = pic.cols * k2;
	Mat img(row, col, CV_8UC1, 255);
	for (int iRow = 0; iRow < row; iRow++)
	{
		for (int iCol = 0; iCol < col; iCol++)
		{
			img.ptr<uchar>(iRow)[iCol] = pic.ptr<uchar>(int(i_ * iRow))[int(j_ * iCol)];
		}
	}
	imshow("Downsampling", img);
	waitKey(0);
	return "Finished!";
}




int main() 
{
	Mat img = imread("D:\\mb\\Lena.jpg", IMREAD_GRAYSCALE);
	cout << Downsampling(0.5,0.5,img) << endl;
	return 0;
}
