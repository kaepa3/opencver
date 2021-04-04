//
//
// (c)Copyright Spacesoft corp., 2019 All rights reserved.
//                               Hiro KITAYAMA
//
#include "common.h"

using namespace cv;
using namespace std;

// mulMask
Mat mulMat(const Mat mat, const Mat table)
{
    Mat dst, mat32f, table32f, dst32f;

    mat.convertTo(mat32f, CV_32FC3);
    table.convertTo(table32f, CV_32FC3);
    table32f /= 255.0f;
    multiply(mat32f, table32f, dst32f);
    dst32f.convertTo(dst, CV_8UC3);

    return dst;
}
