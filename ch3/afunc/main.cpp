#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma(lib, "opencv_world400.lib");
#include <string>

using namespace cv;
using namespace std;

void cvt(InputArray inputSrc, OutputArray outputDst) {
  Mat src = inputSrc.getMat();
  Mat dst = outputDst.getMat();
  flip(src, dst, 1);
}

int main(int argc, char *argv[]) {
  Mat src, dst;
  src = imread("../../images/sample.jpg");
  dst.create(src.size(), src.type());
  cvt(src, dst);

  imshow("src", src);
  imshow("dst", dst);

  waitKey(0);

  return 0;
}
