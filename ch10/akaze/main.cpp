#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/photo.hpp"
#include <algorithm>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

  Mat src1, src2, dst;
  imread("../../images/face.png", IMREAD_COLOR).copyTo(src1);
  cv::Point2f center =
      cv::Point2f((src1.cols / 2), (src1.rows / 2)); //図形の中心
  Mat change = getRotationMatrix2D(center, 3, 1);
  warpAffine(src1, src2, change, src1.size(), cv::INTER_CUBIC,cv::BORDER_CONSTANT,cv::Scalar(0, 0, 0)); //画像の変換(アフィン変換)


  vector<KeyPoint> keypoint1, keypoint2;
  Ptr<FeatureDetector> detector = AKAZE::create();

  detector->detect(src1, keypoint1);
  detector->detect(src2, keypoint2);

  Mat descriptor1, descriptor2;
  Ptr<DescriptorExtractor> extractor = AKAZE::create();

  extractor->compute(src1, keypoint1, descriptor1);
  extractor->compute(src2, keypoint2, descriptor2);

  vector<DMatch> matches;
  Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce");
  matcher->match(descriptor1, descriptor2, matches);
  printf("hoge:%d\n", matches.max_size());

  drawMatches(src1, keypoint1, src2, keypoint2, matches, dst);
  printf("draw\n");

  imshow("dst", dst);

  waitKey(0);

  return 0;
}
