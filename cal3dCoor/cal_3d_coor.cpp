#include "cal_3d_coor.h"
#include <ostream>
#include <fstream>

void cal_3d_coor(Mat skeleton, vector<Vec3f>& allPoints, Mat K, Vec3f& coeff, int &z_count, int z_threshold)
{

	float f_x = K.at<float>(0, 0);
	float f_y = K.at<float>(1, 1);
	float c_x = K.at<float>(0, 2);
	float c_y = K.at<float>(1, 2);

	float m_A = coeff[0];
	float m_B = coeff[1];
	float m_C = coeff[2];

	int height = skeleton.rows;
	int width = skeleton.cols;
	//ofstream fout("C://test_pic//data.txt");  /* 保存标定结果的文件 */    

	/*偏角，转化为弧度制*/
	float alpha = 24;
	float rad_alpha = alpha / 180 * 3.1415926;


	Vec3f _3d_coor;
	Vec3f _3d_coor_transformed;
	/*内参数矩阵的逆矩阵*/
	Mat K_Inverse;
	invert(K, K_Inverse);
	for (int i = 0; i<480; i++)
	{

		for (int j = 0; j<640; j++)
		{
			int value = skeleton.at<uchar>(i, j);
			if (value != 0)
			{
				Point2f temp(i, j);
				//fout<<"结构光点"<<temp<<endl;
				//cout<<"结构光点"<<temp<<endl;
				float z = m_C*f_x*f_y / (f_x*f_y - m_A*f_y*(j - c_x) - m_B*f_x*(i - c_y));
				_3d_coor[0] = (j - c_x)*z / f_x;
				_3d_coor[1] = (i - c_y)*z / f_y;
				_3d_coor[2] = z;


				//坐标转换之后的xyz坐标
				_3d_coor_transformed[0] = _3d_coor[0];
				_3d_coor_transformed[1] = _3d_coor[1] * cos(rad_alpha) - _3d_coor[2] * sin(rad_alpha);
				_3d_coor_transformed[2] = _3d_coor[1] * sin(rad_alpha) + _3d_coor[2] * cos(rad_alpha);

				//判断一下超过阈值点的个数，判断是否是刮板
				if (z>z_threshold)
					z_count++;


				//	fout<<_3d_coor<<endl;
				allPoints.push_back(_3d_coor_transformed);
			}

		}
	}
	//fout.close();
}