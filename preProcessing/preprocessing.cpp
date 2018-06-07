#include "preprocessing.h"

void preprocessing(Mat& Input, Mat& uMask, Mat& skeleton,Size ImageSize,int& count)
{
	int width = ImageSize.width;
	int height = ImageSize.height;

	//取反
	bitwise_not(uMask, uMask);
	Mat  b_thresholded, g_thresholded;
	vector<Mat> channels_bgr;
	split(Input, channels_bgr);
	threshold(channels_bgr[1], g_thresholded, 200, 255, THRESH_BINARY);


	//逻辑操作，去除背景
	Mat outputimage;
	bitwise_and(uMask, g_thresholded, outputimage);

	//形态学处理，腐蚀
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));


	erode(outputimage, outputimage, element);


	//生成骨架
	vector<int> center_line;

	//初始化存储点的向量
	for (int i = 0; i<width; i++)
	{
		center_line.push_back(0);
	}

//计算骨架上点的个数

	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		if (outputimage.at<uchar>(i, j) != 0 && center_line[j] == 0)
		{
			center_line[j] = 1;
			skeleton.at<uchar>(i, j) = 255;

			count++;
		}
	}

}