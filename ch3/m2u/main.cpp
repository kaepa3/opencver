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
  {

    Mat mat = imread(path);
    UMat umat;
    mat.copyTo(umat);
  }
  {
    UMat umat;
    imread(path).copyTo(umat);
  }
  {
    Mat mat = imread(path);
    UMat umat= mat.getUMat(ACCESS_RW);
  }
  
  {

    UMat umat;
    imread(path).copyTo(umat);
    Mat mat = umat.getMat(ACCESS_RW);
  }


}
