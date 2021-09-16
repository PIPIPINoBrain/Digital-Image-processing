/*lamda增强
logI = lamda*logL+C    最后求I   lamda
*/
string Lamda_enhance(Mat pic)
{
	cout << (int)pic.ptr<uchar>(0)[0] << endl;
	float lamda = 1.05, c = 0.01;
	for (int iRow = 0; iRow < pic.cols; iRow++)
	{
		for (int iCol = 0; iCol < pic.rows; iCol++)
		{
			double tem = exp(lamda * log(pic.ptr<uchar>(iRow)[iCol]) + c);
			if (tem >= 255)
			{
				pic.ptr<uchar>(iRow)[iCol] = 255;
			}
		}
	}
	return "Finished";
}
int main()
{
	cv::Mat img = cv::imread("D:\\mb\\Lena.jpg", cv::IMREAD_GRAYSCALE);
	cout << Lamda_enhance(img) << endl;
	cv::imshow("lena", img);
	waitKey(0);
	return 0;
}
