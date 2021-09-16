#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;
  

//直方图均衡化
string HistEqualize(Mat img)
{
	float array[256] = { 0 };
	for (int iRow = 0; iRow < img.rows; iRow++)//求出灰度直方图的数组
	{
		uchar* p = img.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < img.cols; iCol++)
		{
			for (int iCount = 0; iCount < 256; iCount++)
			{
				if (p[iCol] == iCount)
					array[iCount] += 1;
			}
		}
	}
	int N_f = img.rows * img.cols;
	for (int iCount = 0; iCount < 256; iCount++)//灰度分布概率
	{
		array[iCount] = array[iCount]/N_f;
	}
	for (int i = 0; i < 256; i++)
		cout << array[i] << " ";


	array[0] = 0;
	for (int iCount = 1; iCount < 256; iCount++)//灰度值累计分布概率
	{
		array[iCount] = array[iCount] + array[iCount - 1];
	}

	for (int iRow = 0; iRow < img.rows; iRow++)//求出灰度直方图的数组
	{
		uchar* p = img.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < img.cols; iCol++)
		{
			for (int iCount = 0; iCount < 256; iCount++)
			{
				if (p[iCol] == iCount)
					p[iCol] = array[iCount] * 255;
			}
		}
	}
	return "Finished";
}


int main()
{
	cv::Mat img = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout << HistEqualize(img) << endl;
	cv::imshow("lena", img);
	waitKey(0);

}
