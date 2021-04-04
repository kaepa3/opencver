#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include "opencv2/core/cvstd.hpp"
#include "opencv2/core/ocl.hpp"
#include <cstdio>

using namespace cv;
using namespace std;

vector<float> ocv(const bool useOpenCL, const int maxSize) {

    const int numRepeat = 100;

    CStopwatch sw;
    vector<float> r;

    ocl::setUseOpenCL(useOpenCL);

    for (int size = 16; size < maxSize; size *= 2) {
        UMat usrc1(size, size, CV_32F, Scalar(1)), udst;

        sw.Start();
        for (int n = 0; n < numRepeat; n++) {
            exp(usrc1,  udst);
        }
        sw.StopAndAccumTime();

        printf("%5d x %5d:  %20.16f\n", size, size, sw.getElapsedTime());
        r.push_back(sw.getElapsedTime());
    }
    return r;
}

int main(int argc, char *argv[]) {
    try {
        int maxSize = 4096;
        if (!ocl::haveOpenCL()) {
            printf("no have opencl!!!");
            return 0;
        }
        cv::String oclDevName = ocl::Context::getDefault().device(0).name();
        cout << "OpenCL Devide= " << oclDevName << endl << endl;
        cout << "OpenCL Mode :" << endl;
        vector<float> ocl = ocv(true, maxSize);

        cout << endl;

        cout << "no OpenCL Mode:" << endl;
        vector<float> nocl = ocv(false, maxSize);

        printf("\n OpenCL Mode/ no OpenCL Mode:\n");
        for (int n = 0; n < nocl.size(); n++) {
            printf("%13.5f\n", nocl[n] / ocl[n]);
        }
    } catch (const char *str) {
        cout << str << endl;
    }
    return 0;
}
