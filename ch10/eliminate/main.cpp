#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/photo.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

  UMat src, dst;
  imread("../../images/sample.jpg").copyTo(src);

  MatSize size = src.size;
  UMat mask = UMat::ones(size[0], size[1], CV_8UC1);
  
  rectangle(mask, Rect(300,300,400,400),  Scalar(255,0,0), -1);

  inpaint(src, mask, dst, 1, INPAINT_TELEA);
  imwrite("mask.jpg", mask);

  imshow("src", src);
  imshow("dst", dst);

  
  waitKey(0);

  return 0;
}
