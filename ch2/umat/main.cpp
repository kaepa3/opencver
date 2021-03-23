#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    string path = "../../image/sample.jpg";
  {
    Mat mat imread(path);
    UMat umat;
    mat.coppyTo(umat);
  }
  {
    UMat umat;
    imread(path).coppyTo(umat);
  }

}
