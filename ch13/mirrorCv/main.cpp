#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include "opencv2/core/cvstd.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstdio>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    try {
        Mat src, dst;
        src = imread("../../images/face.png");

        flip(src, dst, 1);
        imshow("src", src);
        imshow("dst", dst);

        waitKey(0);
    } catch (const char *str) {
        cout << str << endl;
    }
    return 0;
}
