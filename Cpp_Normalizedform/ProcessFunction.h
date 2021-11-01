/////----------------------------------------------------------------------------------------------------------------------------
// COPYRIGHT(C) 2021 MB
// ALL RIGHRS RESERVED
// 
////------------------------------------------------------------------------------------------------------------------------------


#ifndef __PictureProcess_H___
#define __PictureProcess_H___

#include<iostream>
#include<fstream>
#include<vector>
#include<opencv2/opencv.hpp>

#include"UnionUse.h"




class IOtxt
{
public:
	IOtxt();
	~IOtxt();

	int Read(std::string file_path);        //输入TXT文件路径，读取TXT内信息

	int Write(uchar* pTem,                  //输入：数组指针
		int iM,								//输入：数组宽高
		int iN,
		std::string file_path);             //输入：写入TXT文件地址

private:
	int m_IOtxt;
};


class TxtoMat
{
public:
	TxtoMat();
	~TxtoMat();

	int Transform(std::string file_path);   //输入：TXT文件位置，将Txt文件转化为Mat文件并显示

private:
	int T_tom;
};




class FilterSplit
{
public:
	FilterSplit();
	~FilterSplit();

	int Split_Getmin(cv::Mat pic,         //输入：待分割图像
		int i_MRows,					  //输入：分割块数，M*N块
		int i_NCols, 
		uchar* pMin);                     //每块最小的数组成的数组  一般为i_MRows * i_NCols

	int Split_Getmax(cv::Mat pic,		  //输入：待分割图像
		int i_MRows,                      //输入：分割块数，M*N块
		int i_NCols, 
		uchar* pMax);                     //每块最大的数组成的数组  一般为i_MRows * i_NCols

private:
	int Filter_n = 0;
};
#endif
