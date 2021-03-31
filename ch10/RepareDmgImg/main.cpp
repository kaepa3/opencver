#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/photo.hpp"
#include <iostream>
#include <string>
#include <thread>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

  Mat src, gray, dst;
  imread("../../images/empty.jpg").copyTo(src);

  cvtColor(src, gray, COLOR_RGB2GRAY);
  Mat mask;
  equalizeHist(gray, mask);
  threshold(mask, mask, 243, 1, THRESH_BINARY);
  imwrite("mask.jpg", mask);

  inpaint(src, mask, dst, 3, INPAINT_TELEA);

  imshow("src", src);
  imshow("dst", dst);

  waitKey(0);

  return 0;
}
