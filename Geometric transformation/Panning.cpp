#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;
  

//输入 图片， 平移多少位，向下多少位置
string Panning(Mat pic, int w_Range, int h_Range)
{
	int row = pic.rows, col = pic.cols;
	Mat Moved_pic(row + 500, col + 500, CV_8UC1, 255);  //扩大范围来平移
	for (int iRow = 0; iRow < row; iRow++)
	{
		uchar* p_M = Moved_pic.ptr<uchar>(iRow + w_Range);
		uchar* p = pic.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < col; iCol++)
		{
			p_M[iCol + h_Range] = p[iCol];                
		}
	}
	imshow("large", Moved_pic);                     //展示一下
	waitKey(0);
	return "Fiished";
}
	

int main()
{
	Mat img = imread("D:\\mb\\Lena.jpg", IMREAD_GRAYSCALE);
	Panning(img, 50, 50);
	return 0;
}
