#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

/*用来计算截面积*/
/*diatance是相机距离 面板的距离,用来点到刮板的实际距离，width是刮板的宽度,用来剔除不需要的点*/
float cal_area(vector<Vec3f> pointsAfterTransform, float distance, float width);