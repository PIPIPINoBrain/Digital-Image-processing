/////--------------------------------------------------------------------------------------------------------------------
//*Copyright(C) 2016 Roiland Co.Ltd
//*ALL RIGHTS RESERVED
//*	
//*This source code is the confidential of Roiland Co.Ltd
//*Disclosure to the third party written consent from Roiland Co.Ltd
//*IS STRONGLY PROHIBITE AND WILL BE PROSECUTED.	
//*
/////--------------------------------------------------------------------------------------------------------------------
#include <fstream>
#include <iostream>

#include "UnionUse.h"

//  [5/17/2016 linshu.bai]
using namespace std;
//------------------------------------------------------------------------------------------------------------------------
// 函数功能 ：LOG保存
void ErrorTrace(const char* psError,			//输入：错误信息
	const char* psFile,					//输入：哪个文件
	const char* psFunction,				//输入：哪个函数
	int iLine,						//输入：哪一行
	const char* psLogPath)                //输入：LOG位置
{
#ifdef _ERROR_TRACE
	std::fstream file;

	file.open(psLogPath, std::ios::app);

	file << "//---------------------------------Start-------------------------------------" << std::endl;
	file << "Function:" << psFunction << std::endl << "Line: " << iLine << std::endl << "Error: " << psError << std::endl;
	file << "//----------------------------------End--------------------------------------" << std::endl;

	file.close();
#endif
}

const char* GetErrorType(int iMode)
{
	if (iMode > 0)
	{
		return "ErrorType Error\0";
	}

	const char* p = NULL;

	if (iMode == DIP_USEERROR)
	{
		p = "DIP_USEERROR";
	}
	if (iMode == DIP_ERROR)
	{
		p = "DIP_ERROR";

	}
	if (iMode == DIP_MEMERROR)
	{
		p = "DIP_MEMERROR";
	}
	if (iMode == DIP_FILEERROR)
	{
		p = "DIP_FILEERROR";
	}
	if (iMode == DIP_ERROR)
	{
		p = "DIP_ERROR";
	}
	return p;
}
int DebugMat(char* Path, cv::Mat A, bool bActicve)
{
#ifdef _DEBUG_BUFF

	if (!bActicve)
	{
		return 0;
	}

	ofstream ofile;
	ofile.open(Path);

	int a = A.type();

	if ((A.type() != CV_32F) && (A.type() != CV_8U) && (A.type() != CV_16U))
	{
		return DIP_USEERROR;
	}

	if (!ofile)
	{
		return DIP_USEERROR;
	}

	if (A.type() == CV_8U)
	{
		for (int iRow = 0; iRow < A.rows; iRow++)
		{
			uchar* data_preRow = A.ptr<uchar>(iRow);

			for (int iCol = 0; iCol < A.cols; iCol++)
			{
				//cout << data_preRow[j] << " ";
				ofile << data_preRow[iCol] << " ";
			}
			ofile << endl;
		}
	}
	if (A.type() == CV_32F)
	{
		for (int iRow = 0; iRow < A.rows; iRow++)
		{
			float* data_preRow = A.ptr<float>(iRow);

			for (int iCol = 0; iCol < A.cols; iCol++)
			{
				float a = data_preRow[iCol];
				ofile << data_preRow[iCol] << " ";
			}
			ofile << endl;
		}
	}
	if (A.type() == CV_16U)
	{
		for (int iRow = 0; iRow < A.rows; iRow++)
		{
			ushort* data_preRow = A.ptr<ushort>(iRow);

			for (int iCol = 0; iCol < A.cols; iCol++)
			{
				ushort a = data_preRow[iCol];

				ofile << data_preRow[iCol] << " ";
			}
			ofile << endl;
		}
	}

	ofile.close();
#endif
	return 0;
}
