#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
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
  UMat src1, buff, src2, dst;
  imread(path1).copyTo(src1);
  imread(path2).copyTo(buff);
  resize(buff, src2, src1.size());

  src1.copyTo(dst);

  Rect roi = Rect(src1.cols / 4, src1.rows / 4, src1.cols / 2, src1.rows / 2);
  UMat src1Roi(src1, roi);
  UMat src2Roi(src2, roi);
  UMat dstRoi(dst, roi);

  add(src1Roi, src2Roi, dstRoi);

  
  imshow("src1", src1);
  imshow("src2", src2);
  imshow("dst", dst);

  waitKey(0);
}
