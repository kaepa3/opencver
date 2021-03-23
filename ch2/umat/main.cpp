#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <opencv2/opencv.hpp>
#pragma(lib, "opencv_world400.lib");
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

  string path = "../../images/sample.jpg";
  Mat src, dst;
  src = imread(path);
  cvtColor(src, dst, COLOR_RGB2GRAY);
  imshow("src", src);
  imshow("dst", dst);

  waitKey(0);
}
