#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/photo.hpp"
#include "opencv2/stitching.hpp"
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

  vector<Mat> srcs;
  for (int n = 0; n < 2; n++) {
    Mat src;
    string path = format("../../images/dev_%d.png", n);
    imread(path).copyTo(src);
    if (src.empty()) {
      printf("read error!!!");
      return 0;
    }
    srcs.push_back(src);
    imshow(format("src:%d"), n);
  }
  Ptr<Stitcher> stt = Stitcher::create(Stitcher::PANORAMA);
  Mat dst;
  Stitcher::Status status = stt->stitch(srcs, dst);
  if (status != Stitcher::OK) {
    printf("error!!!!");
    return 0;
  }
  imshow("dst", dst);
  waitKey(0);

  return 0;
}
