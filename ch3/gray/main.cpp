#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma(lib, "opencv_world400.lib");
#include <string>

using namespace cv;
using namespace std;

void cvt (InputArray inputSrc){
    Mat src = inputSrc.getMat();
    Mat dst ;
    cvtColor(src,dst, COLOR_RGB2GRAY);

    imshow("src", src);
    imshow("dst", dst);
}
int main(int argc, char *argv[]) {
    UMat usrc;

    Mat src = imread("../../images/sample.jpg");
    cvt(src);
    waitKey(0);

    src.copyTo(usrc);
    cvt(usrc);
    
    waitKey(0);

    return 0;
}
