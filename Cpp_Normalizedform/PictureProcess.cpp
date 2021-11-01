/////----------------------------------------------------------------------------------------------------------------------------
// COPYRIGHT(C) 2021 MB
// ALL RIGHRS RESERVED
// 
////------------------------------------------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<opencv2/opencv.hpp>


#include"ProcessFunction.h"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("D:\\mb\\lena.jpg",cv::IMREAD_GRAYSCALE);
	FilterSplit Lena;
	IOtxt a;
	TxtoMat b;
	int m = 128, n = 128;
	uchar* miMax = new uchar[m*n];
	Lena.Split_Getmax(img, m, n, miMax);
	

	a.Write(miMax, m, n, "C:\\Users\\i\\Desktop\\c.txt");
    int iRet = a.Read("C:\\Users\\i\\Desktop\\c.txt");
	if (iRet != DIP_SUCCESS)
	{
		return iRet;
	}

	b.Transform("C:\\Users\\i\\Desktop\\c.txt");
	delete [m*n]miMax;



	uchar* miMin = new uchar[m*n];
	Lena.Split_Getmin(img, m, n, miMin);
	a.Write(miMin, m, n, "C:\\Users\\i\\Desktop\\c.txt");
	a.Read("C:\\Users\\i\\Desktop\\c.txt");
	b.Transform("C:\\Users\\i\\Desktop\\c.txt");
	delete [m*n]miMin;

	return 0;
}

