#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma(lib, "opencv_world400.lib");
#include <string>

using namespace cv;
using namespace std;

void add1mat(const Mat& mat){
    Mat dst = mat + 1;
    cout << "dst=" << dst << endl << endl;
}

void add1array(const InputArray inputSrc){
    Mat src = inputSrc.getMat();
    Mat dst = src + 1;
    cout << "dst=" << dst << endl << endl;
}
int main(int argc, char *argv[]) {
    Mat mat = (Mat_<float>(3,3) << 1,2,3,4,5,6,7,8,9);
    cout << "mat=" << mat << endl << endl;

    add1mat(mat);
    add1array(mat);

    return 0;
}
