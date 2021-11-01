/////--------------------------------------------------------------------------------------------------------------------
//*Copyright(C) 2017 Innno Co.Ltd
//*ALL RIGHTS RESERVED
//*	
//*This source code is the confidential of Innno Mr Mab
//*Disclosure to the third party written consent from Innno Co.Mab
//*IS STRONGLY PROHIBITE AND WILL BE PROSECUTED.	
//*
/////--------------------------------------------------------------------------------------------------------------------

//  [5/17/2016 linshu.bai]

#ifndef _UNIONUSE_H
#define _UNIONUSE_H	

#include "stdio.h"


//#include "cv.h"
//#include "highgui.h"

#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"

typedef unsigned int uint;
// 表示函数的返回状态

#define		BYTE					unsigned char
#define		ALIGN4					0xfffffffc

#define		HISTO_BIN				256

//函数返回类型：DIP：Digital Image Process
#define  DIP_SUCCESS		0			//成功
#define  DIP_USEERROR		-1			//函数输入参数出错
#define  DIP_MEMERROR		-2			//内存申请失败
#define  DIP_FILEERROR		-3			//文件有误
#define  DIP_ERROR			-4			//程序逻辑错误
#define  DIP_CUDAERROR		-5			//CUDA传出错

typedef unsigned char uchar;

#define ERRORLOCATION	__FILE__,__FUNCTION__,__LINE__

void ErrorTrace(const char* psError,			//输入：错误信息
	const char* psFile,					//输入：哪个文件
	const char* psFunction,				//输入：哪个函数
	int iLine,						//输入：哪一行
	const char* psLogPath = "./Log.txt");	//输入：LOG位置
//---------------------------------------------------------------------------------------------------------------------------
// 函数功能 ：得到错误类型
const char* GetErrorType(int iMode);
//---------------------------------------------------------------------------------------------------------------------------

// 函数功能 ：Buff查看保存至txt
template<typename T>
int DebugBuff(char* Path,		    	//输入：文件保存路径
	T* pBuff,					//输入：图像buff
	int iHight = 512,			//输入：图像高
	int iWidth = 512,			//输入：图像宽
	int iColorMode = 0,		//输入：是否是颜色
	int iWhichChannl = 0)		//输入：图像彩色的话，哪个通道。
{
	//assert(pBuff);
	//if(iColorMode == 1)assert((iWhichChannl>-1)||(iWhichChannl<3)	);
	//if(iColorMode == 2)assert((iWhichChannl>-1)||(iWhichChannl<4)	);
#ifdef _DEBUG_BUFF
	short a = 0;
	int num = 0;
	FILE* pFile = fopen(Path, "w");
	if (pFile == NULL)
	{
		return -1;
	}

	if (iColorMode == 0)
	{
		for (int iRow = 0; iRow < iHight; iRow++)
		{
			for (int iCol = 0; iCol < iWidth; iCol++)
			{
				a = pBuff[iCol + iRow * iWidth];
				//fprintf(pFile,"%d ",pBuff[iCol+iRow*iWidth]);
				fprintf(pFile, "%d ", a);
			}
			fprintf(pFile, "\n");
		}
	}
	if (iColorMode == 1)
	{
		for (int iRow = 0; iRow < iHight; iRow++)
		{
			for (int iCol = 0; iCol < iWidth; iCol++)
			{
				a = pBuff[iCol * 3 + iWhichChannl + iRow * iWidth * 3];
				fprintf(pFile, "%d ", a);
			}
			fprintf(pFile, "\n");
		}
	}
	if (iColorMode == 2)
	{
		for (int iRow = 0; iRow < iHight; iRow++)
		{
			for (int iCol = 0; iCol < iWidth; iCol++)
			{
				a = pBuff[iCol/**4+iWhichChannl*/ + iRow * iWidth];
				fprintf(pFile, "%d ", a);
				//num++;
			}
			fprintf(pFile, "\n");
		}
	}

	fclose(pFile);
#endif
	return 0;
}

int DebugMat(char* Path, cv::Mat A, bool bActicve);

#endif
