#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
using namespace cv;
  

//极坐标处理的旋转
//step1:正变换  p=sqrt(x*x+y*y);theta = arctan(y/x)
//step2:逆变换  x = p*cos(theta);y = p*sin(theta)

string rotation(Mat pic, int angle)
{
	int row = pic.rows;
	int col = pic.cols;
	static float list_P[512][512] = {0};
	static float list_Theta[512][512] = {0};
	//static float** list_P = (float**)malloc(sizeof(float) * row * col);
	//static float** list_Theta = (float**)malloc(sizeof(float) * row * col);            //用来存放p 和 theta的数组

	for (int i_Row = 0; i_Row < row; i_Row++)
	{
		float* p_P = list_P[i_Row];
		float* p_Theta = list_Theta[i_Row];
		for (int i_Col = 0; i_Col < col; i_Col++)
		{
			p_P[i_Col] = sqrt(i_Row * i_Row + i_Col * i_Col);                 //计算P和theta数组中的值,theta在-Pi — Pi间
			p_Theta[i_Col] = atan2(i_Col, i_Row) + (3.1415926 * angle/180);     
		}
	}

	static int list_Row[512][512] = { 0 };
	static int list_Col[512][512] = { 0 };
	//static int** list_Row = (int**)malloc(sizeof(int) * row * col);               //用来存放旋转后的行列坐标
	//static int** list_Col = (int**)malloc(sizeof(int) * row * col);

	for (int i_Row = 0; i_Row < row; i_Row++)
	{
		int* p_Row = list_Row[i_Row];
		int* p_Col = list_Col[i_Row];
		for (int i_Col = 0; i_Col < col; i_Col++)
		{
			p_Row[i_Col] = int(list_P[i_Row][i_Col] * cos(list_Theta[i_Row][i_Col]));    //计算旋转后的行列坐标
			p_Col[i_Col] = int(list_P[i_Row][i_Col] * sin(list_Theta[i_Row][i_Col]));
		}
	}

	int min_Row = 2000, max_Row = 0;
	int min_Col = 2000, max_Col = 0;
	for (int i_Row = 0; i_Row < row; i_Row++)
	{
		for (int i_Col = 0; i_Col < row; i_Col++)
		{
			if (list_Row[i_Row][i_Col] > max_Row)
			{
				max_Row = list_Row[i_Row][i_Col];
			}
			if (list_Row[i_Row][i_Col] < min_Row)
			{
				min_Row = list_Row[i_Row][i_Col];
			}
			if (list_Col[i_Row][i_Col] > max_Col)
			{
				max_Col = list_Col[i_Row][i_Col];
			}
			if (list_Col[i_Row][i_Col] < min_Col)
			{
				min_Col = list_Row[i_Row][i_Col];
			}
		}                                                                //计算出旋转后坐标的最大最小值
	}
	
	Mat img(max_Row - min_Row+2, max_Col - min_Col+2, CV_8UC1, 255);              //按照最大最小坐标范围生成图像

	for (int iRow = 0; iRow < row; iRow++)
	{
		for (int iCol = 0; iCol < col; iCol++)
		{
			img.ptr<uchar>(list_Row[iRow][iCol]-min_Row)[list_Col[iRow][iCol] - min_Col] = pic.ptr<uchar>(iRow)[iCol];
		}
	}

	for (int iRow = 0; iRow < max_Row - min_Row + 2; iRow++)
	{
		for (int iCol = 0; iCol < max_Col - min_Col + 2; iCol++)
		{
			if (img.ptr<uchar>(iRow)[iCol] == 255&& img.ptr<uchar>(iRow)[iCol - 1]!=255&& img.ptr<uchar>(iRow)[iCol + 1]!=255&& img.ptr<uchar>(iRow-1)[iCol]!=255&& img.ptr<uchar>(iRow+1)[iCol]!=255)
			{
				img.ptr<uchar>(iRow)[iCol] = img.ptr<uchar>(iRow)[iCol-1];
			}
		}
	}
	
	imshow("22", img);
	waitKey(0);
	//free(list_P);
	//free(list_Theta);
	//free(list_Row);
	//free(list_Col);
	return "Finished";
}
	

int main() 
{
	Mat img = imread("D:\\mb\\Lena.jpg", IMREAD_GRAYSCALE);
	cout << rotation(img,45) << endl;
	return 0;
}

