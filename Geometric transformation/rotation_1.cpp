#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
using namespace cv;
  


// i = i*cos(theta) - j*sin(theta)
// j = i*sin(theta) - j*cos(theta)
//直角坐标旋转,算法原因吧，0-90度举例，只有45或90能够保持原样（不包含间隙）,应该是取整产生的归并现象
string rotation(Mat pic)
{
	static int pRow[512][512] = { 0 };
	static int pCol[512][512] = { 0 };
	int row = pic.rows;
	int col = pic.cols;
	cout << row << col << endl;


/*	int** pRow = (int**)malloc(sizeof(int) * row * col);
	int** pCol = (int**)malloc(sizeof(int) * row * col);  */                  //两个数组用来存储每个像素的行，列的信息
	float theta = 45 * 3.1415926 / 180;                                     //角度

		


	for (int iRow = 0; iRow < row; iRow++)
	{
		for (int iCol = 0; iCol < col; iCol++)
		{
			pRow[iRow][iCol] = int((iRow + 1)* cos(theta) - (iCol + 1) * sin(theta));    //将行列信息计算并存储下来
			pCol[iRow][iCol] = int((iCol + 1)* sin(theta) + (iRow + 1) * cos(theta));
		}
	}
	//for (int iRow = 0; iRow < row; iRow++)
	//{
	//	for (int iCol = 0; iCol < col; iCol++)
	//	{
	//		cout << pRow[iRow][iCol] <<" "<< pCol[iRow][iCol] << endl; 
	//	}
	//}

	int min_row = 1500, max_row = 0;
	int min_col = 1500, max_col = 0;
	for (int iRow = 0; iRow < row; iRow++)
	{
		for (int iCol = 0; iCol < col; iCol++)
		{
			if (pRow[iRow][iCol] < min_row)
			{
				min_row = pRow[iRow][iCol];
			}
			if (pRow[iRow][iCol] > max_row)
			{
				max_row = pRow[iRow][iCol];
			}
			if (pCol[iRow][iCol] < min_col)
			{
				min_col = pCol[iRow][iCol];
			}
			if (pCol[iRow][iCol] > max_col)
			{
				max_col = pCol[iRow][iCol];
			}
		}
	}
	cout << max_row << " " << min_row << " " << max_col << " " << min_col << endl;                    
	cout << max_row - min_row <<" "<< max_col - min_col << endl;                          //求出最大最小区间，填充像素
	Mat img(int(max_row - min_row+2), int(max_col - min_col + 2), CV_8UC1, 255);



	if(min_row<0 && min_col>0)                                                           //进行分类讨论，像素移植
	{
		for (int iRow = 0; iRow < row; iRow++)
		{
			for (int iCol = 0; iCol < col; iCol++)
			{
				img.ptr<uchar>(pRow[iRow][iCol] - min_row+1)[pCol[iRow][iCol]] = pic.ptr<uchar>(iRow)[iCol];
			}
		}
	}
	if (min_row > 0 && min_col < 0)
	{
		for (int iRow = 0; iRow < row; iRow++)
		{
			for (int iCol = 0; iCol < col; iCol++)
			{
				img.ptr<uchar>(pRow[iRow][iCol])[pCol[iRow][iCol] - min_col] = pic.ptr<uchar>(iRow)[iCol];
			}
		}
	}
	if (min_row < 0 && min_col < 0)
	{
		for (int iRow = 0; iRow < row; iRow++)
		{
			for (int iCol = 0; iCol < col; iCol++)
			{
				img.ptr<uchar>(pRow[iRow][iCol] - min_row)[pCol[iRow][iCol] - min_col] = pic.ptr<uchar>(iRow)[iCol];
			}
		}
	}
	if (min_row > 0 && min_col > 0)
	{
		for (int iRow = 0; iRow < row; iRow++)
		{
			for (int iCol = 0; iCol < col; iCol++)
			{
				img.ptr<uchar>(pRow[iRow][iCol])[pCol[iRow][iCol]] = pic.ptr<uchar>(iRow)[iCol];
			}
		}
	}


	//插值（邻近，均值）这里用的均值插值
	for (int iRow = 1; iRow <int(max_row - min_row+1); iRow++)
	{
		for (int iCol = 1; iCol < int(max_col - min_col+1); iCol++)
		{
			if ((img.ptr<uchar>(iRow)[iCol]==255 )&& img.ptr<uchar>(iRow - 1)[iCol] != 255 && img.ptr<uchar>(iRow + 1)[iCol] != 255 && img.ptr<uchar>(iRow)[iCol - 1] != 255 && img.ptr<uchar>(iRow)[iCol + 1] != 255)
			{

				img.ptr<uchar>(iRow)[iCol] = int((img.ptr<uchar>(iRow-1)[iCol]+ img.ptr<uchar>(iRow + 1)[iCol]+ img.ptr<uchar>(iRow)[iCol-1]+ img.ptr<uchar>(iRow)[iCol+1])/4);

			}
		}
	}


	imshow("11", img);
	waitKey(0);
	////free(pRow);
	//free(pCol);
	return "Finished";
}

	

int main() 
{
	Mat img = imread("D:\\mb\\Lena.jpg", IMREAD_GRAYSCALE);
	cout << rotation(img) << endl;
	return 0;
}
