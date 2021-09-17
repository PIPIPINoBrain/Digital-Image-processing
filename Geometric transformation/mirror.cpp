#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace std;
using namespace cv;
  


//水平：i = i； j = col - j -1 
//垂直：i = row - i -1; j = j
string mirror(Mat pic)
{
	//Horizontal mirroring,水平镜像
	int row = pic.rows;
	int col = pic.cols;
	Mat H_img(row, col, CV_8UC1, 255);
	for (int iRow = 0; iRow < row; iRow++)
	{
		uchar* p_H = H_img.ptr<uchar>(iRow);
		uchar* po_H = pic.ptr<uchar>(iRow);
		for (int iCol = 0; iCol < col; iCol++)
		{
			p_H[iCol] = po_H[col - iCol - 1];
		}
	}
	imshow("Horizontal mirroring", H_img);
	waitKey(0);

	//Vertical mirroring
	Mat V_img(row, col, CV_8UC1, 255);
	for (int iRow = 0; iRow < row; iRow++)
	{
		uchar* p_V = V_img.ptr<uchar>(iRow);
		uchar* po_V = pic.ptr<uchar>(row - iRow - 1);
		for (int iCol = 0; iCol < col; iCol++)
		{
			p_V[iCol] = po_V[iCol];
		}
	}
	imshow("Vertical mirroring", V_img);
	waitKey(0);

	return "Finished";
}

	

int main()
{
	Mat img = imread("D:\\mb\\Lena.jpg", IMREAD_GRAYSCALE);
	cout << mirror(img) << endl;
	return 0;
}
