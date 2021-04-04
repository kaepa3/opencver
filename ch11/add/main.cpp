#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    const int numRepeat = 100;

    int maxSize = 4096;
    CStopwatch matTime, umatTime;

    for (int size = 16; size < maxSize; size *= 2) {
        Mat src1(size, size, CV_32F, Scalar(1));
        Mat src2(src1), dst;
        UMat usrc1(size, size, CV_32F, Scalar(1));
        UMat usrc2(usrc1), udst;

        matTime.Start();
        for (int n = 0; n < numRepeat; n++) {
            add(src1, src2, dst);
        }
        matTime.StopAndAccumTime();

        umatTime.Start();
        for (int n = 0; n < numRepeat; n++) {
            add(usrc1, usrc2, udst);
        }
        umatTime.StopAndAccumTime();

        printf("%5d x %5d: Mat,UMat -> %12.8f, %12.8f, Mat/UMat = %.3f\n", size,
               size, matTime.getElapsedTime(), umatTime.getElapsedTime(),
               matTime.getElapsedTime() / umatTime.getElapsedTime());
    }
    return 0;
}
