//
//
// (c)Copyright Spacesoft corp., 2019 All rights reserved.
//                               Hiro KITAYAMA
//
#include "common.h"

using namespace cv;
using namespace std;

// create cos k mat
Mat createCosMat(const int rows, const int cols)
{
    Mat mat(rows, cols, CV_8UC3, Scalar(0));
    Point center = Point(cols / 2, rows / 2);
    double radius = sqrt(pow(center.x, 2) + pow(center.y, 2));

    for (int y = 0; y < mat.rows; y++)
    {
        for (int x = 0; x < mat.cols; x++)
        {
            // distance from center
            double distance = sqrt(pow(center.x - x, 2) + pow(center.y - y, 2));
            // radius=π, current radian
            double radian = (distance / radius) * (double)CV_PI;
            // cosθ, normalize -1.0～1.0 to  0～1.0
            double Y = (cos(radian) + 1.0) / 2.0;
            // normalize (Y) 0～1.0 to 0.0～255.0
            mat.at<Vec3b>(y, x)[0] =
                mat.at<Vec3b>(y, x)[1] =
                mat.at<Vec3b>(y, x)[2] = (unsigned char)(Y*255.0f);
        }
    }
    return mat;
}
