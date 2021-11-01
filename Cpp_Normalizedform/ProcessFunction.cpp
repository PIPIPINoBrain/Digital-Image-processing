/////----------------------------------------------------------------------------------------------------------------------------
// COPYRIGHT(C) 2021 MB
// ALL RIGHRS RESERVED
// 
////------------------------------------------------------------------------------------------------------------------------------


#include<iostream>
#include<fstream>
#include<vector>
#include<opencv2/opencv.hpp>

#include"ProcessFunction.h"
#include"UnionUse.h"

//读txt文件
IOtxt::IOtxt()
{
	m_IOtxt = 1;
}
IOtxt::~IOtxt() {}


int IOtxt::Read(std::string file_path)
{
	if (file_path == "")
	{
		
		return DIP_USEERROR;
	}
	std::ifstream in(file_path, std::ios::in);
	std::string line;
	if (in)
	{
		while (getline(in, line))
		{
			std::cout << line << std::endl;
		}
	}
	else
		std::cout << "No Such File" << std::endl;
	in.close();

	return DIP_SUCCESS;
}

//写TXT文件
int IOtxt::Write(uchar* pTem, int iM, int iN, std::string file_path)
{
	if (file_path == "" && pTem==NULL && iM<=0 && iN<=0)
	{
		return DIP_USEERROR;
	}


	std::ofstream out(file_path, std::ios::out);

	if (out)
	{
		for (int iRow = 0; iRow < iM; iRow++)
		{
			for (int iCol = 0; iCol < iN; iCol++)
			{
				out << (int)pTem[iRow * iN + iCol] << " ";

			}
			out << std::endl;
		}
	}
	else
		std::cout << "No Such File" << std::endl;
	out.close();
	return DIP_SUCCESS;
}




TxtoMat::TxtoMat()
{
	T_tom = 1;
}
TxtoMat::~TxtoMat() {}

int TxtoMat::Transform(std::string file_path)
{
	if (file_path == "")
	{
		ErrorTrace("DIP_USEERROR", file_path.c_str(), "TxtoMat::Tranform", 89);
		return DIP_USEERROR;
	}

	std::ifstream in(file_path, std::ios::in);
	std::string line;
	if (in)
	{
		int Line_Num = 0, Col_Num = 0;
		std::istringstream iss;
		std::vector<uchar>M_arr = { 0,1 };
		char tem = 0;

		while (getline(in, line))
		{
			Line_Num += 1;
			int i_Line = 0;
			while (line[i_Line])
			{
				if (line[i_Line] == ' ')
				{
					Col_Num++;
				}
				i_Line++;
			}
		}

		in.close();

		std::ifstream in(file_path, std::ios::in);

		Col_Num = Col_Num / Line_Num;
		std::cout << Col_Num << " " << Line_Num << std::endl;

		cv::Mat img(Line_Num, Col_Num, CV_8UC1);

		for (int iRow = 0; iRow < Line_Num; iRow++)
		{
			uchar* p = img.ptr<uchar>(iRow);
			for (int iCol = 0; iCol < Col_Num; iCol++)
			{
				int a = 0;
				in >> a;
				p[iCol] = (uchar)a;
			}
		}

		cv::imshow("img", img);
		cv::waitKey(0);
	}

	else
	{
		ErrorTrace("DIP_FILEERROR", file_path.c_str(), "TxtoMat::Tranform", 142);
		return DIP_FILEERROR;
	}
	return DIP_SUCCESS;
}




FilterSplit::FilterSplit()
{
	Filter_n = 1;
}
FilterSplit::~FilterSplit() {}

int FilterSplit::Split_Getmax(cv::Mat Pic, int i_MRows, int i_NCols, uchar* pMax)
{
	if (i_MRows <= 0 && i_NCols <= 0 && pMax==NULL &&Pic.empty())
	{
		return DIP_USEERROR;
	}

	int iStepC = Pic.cols / i_NCols;
	int iStepR = Pic.rows / i_MRows;
	memset(pMax, 0, i_MRows * i_NCols);

	for (int iRow = 0; iRow < Pic.rows; iRow++)
	{
		uchar* p = Pic.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < Pic.cols; iCol++)
		{
			if ((int)pMax[iCol / iStepC + iRow / iStepR * i_NCols] < p[iCol])
			{
				pMax[iCol / iStepC + iRow / iStepR * i_NCols] = p[iCol];
			}

		}
	}

	return 0;
}

int FilterSplit::Split_Getmin(cv::Mat Pic, int i_MRows, int i_NCols, uchar* pMin)
{
	if (i_MRows <= 0 && i_NCols <= 0 && pMin == NULL && Pic.empty())
	{
		return DIP_USEERROR;
	}

	int iStepC = Pic.cols / i_NCols;
	int iStepR = Pic.rows / i_MRows;
	memset(pMin, 255, i_MRows * i_NCols);

	for (int iRow = 0; iRow < Pic.rows; iRow++)
	{
		uchar* p = Pic.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < Pic.cols; iCol++)
		{
			if ((int)pMin[iCol / iStepC + iRow / iStepR * i_NCols] > p[iCol])
			{
				pMin[iCol / iStepC + iRow / iStepR * i_NCols] = (int)p[iCol];
			}

		}
	}

	return 0;
}
