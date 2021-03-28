#include "opencv2/core/hal/interface.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma(lib, "opencv_world400.lib");
#include <string>

using namespace cv;
using namespace std;

static UMat makeMask(int w, int h) {
  Size sz(w, h);
  UMat mask(sz, CV_8UC1, Scalar());
  Point p0 = Point(w / 4., h / 4);
  Point p1 = Point(w * 3 / 4., h * 3 / 4);
  rectangle(mask, p0, p1, Scalar(255), -1);
  return mask;
}
int main(int argc, char *argv[]) {

  string path1 = "../../images/sample.jpg";
  string path2 = "../../images/sample2.jpg";
  Mat src1, src2, dst;
  src1 = imread(path1);
  src2 = imread(path2);

  UMat mask = makeMask(src1.cols, src1.rows);

  UMat src2Resize;
  resize(src2, src2Resize, Size(src1.cols, src1.rows));

  add(src1, src2Resize, dst, mask);
  imshow("src1", src1);
  imshow("src2", src2);
  imshow("dst", dst);

  waitKey(0);
}
