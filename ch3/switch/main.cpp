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

void cvt(InputArray inputSrc) {
  int type = inputSrc.kind() & _InputArray::KIND_MASK;

  switch (type) {
  case _InputArray::MAT: {
    Mat src = inputSrc.getMat();
    Mat dst;
    flip(src, dst, 1);
    imshow("src", src);
    imshow("dst", dst);
    break;
  }
  case _InputArray::UMAT:
    UMat usrc = inputSrc.getUMat();
    Mat udst;

    cvtColor(usrc, udst, COLOR_RGB2GRAY);
    imshow("usrc", usrc);
    imshow("udst", udst);
    break;
  }
}
int main(int argc, char *argv[]) {

  Mat src = imread("../../images/sample.jpg");
  cvt(src);
  waitKey(0);
  destroyAllWindows();
  
  UMat usrc;
  src.copyTo(usrc);
  cvt(usrc);

  waitKey(0);

  return 0;
}
