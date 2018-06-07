#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void cal_3d_coor(Mat skeleton, vector<Vec3f>& allPoints, Mat K, Vec3f& coeff, int &z_count, int z_threshold);
