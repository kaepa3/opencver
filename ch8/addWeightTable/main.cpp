#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat createCosMat(const int rows, const int cols) {
  Mat mat(rows, cols, CV_8UC3, Scalar(0));
  Point center = Point(cols / 2, rows / 2);
  double radius = sqrt(pow(center.x, 2) + pow(center.y, 2));
  for (int y = 0; y < mat.rows; y++) {
    for (int x = 0; x < mat.cols; x++) {
      double distance = sqrt(pow(center.x - x, 2) + pow(center.y - y, 2));

      double radian = (distance / radius) * (double)CV_PI;

      double Y = (cos(radian) + 1.0) / 2.0;

      mat.at<Vec3b>(y, x)[0] = mat.at<Vec3b>(y, x)[1] = mat.at<Vec3b>(y, x)[2] =
          (unsigned char)(Y * 255.0f);
    }
  }
  return mat;
}

Mat mulMat(const Mat mat, const Mat table) {
  Mat dst, mat32f, table32f, dst32f;

  mat.convertTo(mat32f, CV_32FC3);
  table.convertTo(table32f, CV_32FC3);
  table32f /= 255.0f;
  multiply(mat32f, table32f, dst32f);
  dst32f.convertTo(dst, CV_8UC3);
  return dst;
}


int main(int argc, char *argv[]) {

  string path1 = "../../images/sample.jpg";
  string path2 = "../../images/sample2.jpg";
  Mat src1, buff, src2, dst;
  imread(path1).copyTo(src1);
  imread(path2).copyTo(buff);
  resize(buff, src2, src1.size());

  src1.copyTo(dst);

  Mat weightMat =  createCosMat(src1.rows, src1.cols);
  Mat iWeightMat = Scalar(255,255,255) - weightMat;

  Mat intSrc1, intSrc2;

  intSrc1 = mulMat(src1, weightMat);
  intSrc2 = mulMat(src2, iWeightMat);

  add(intSrc1, intSrc2, dst);

  imshow("src1", src1);
  imshow("src2", src2);
  imshow("dst", dst);

  waitKey(0);
}
