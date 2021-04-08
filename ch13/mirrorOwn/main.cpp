#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include "opencv2/core/cvstd.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/ocl.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <cstdio>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
    try {
		const char* kernelName = "ksample";
		const string kernelSrc = 
			"__kernel void ksample(\n\
			__global uchar* src,int sStep, int sOffset, \n\
			__global uchar* dst,int dStep, int dOffset, \n\
			int dRows, int dCols)\n\
			{\n\
				int x = get_global_id(0);\n\
				int y = get_global_id(1);\n\
			\n\
				if(x>dCols-1 || y>dRows-1)\n\
					return;\n\
			\n\
				int sIndex = mad24(y, sStep, x + sOffset);\n\
				int dIndex = mad24(y, dStep, dCols -x -1 + dOffset);\n\
			\n\
				dst[dIndex] = src[sIndex];\n\
			}\n";

		if(!ocl::haveOpenCL()){
			throw "no OpenCL devices";
		}
		ocl::Context context;
		if(!context.create(ocl::Device::TYPE_GPU))
			throw "Could not create GPU the context!!!";

		ocl::Device(context.device(0));

		UMat src;
		imread("../../images/face.png", IMREAD_GRAYSCALE).copyTo(src);
		UMat dst(src.size(), src.type());

		ocl::ProgramSource programSource(kernelSrc);

		String errMsg;
		String bldOpt = "";

		ocl::Program kPgm = context.getProg(programSource, bldOpt, errMsg);

		ocl::Kernel kernel(kernelName,kPgm);
		kernel.args(ocl::KernelArg::ReadOnlyNoSize(src), ocl::KernelArg::ReadWrite(dst));

		size_t globalSize[]= {(size_t) src.cols, (size_t)src.rows};
		bool success = kernel.run(2, globalSize, NULL, true);
		if(!success){
			throw "Failed execute the kernel";
		}

		imshow("src", src);
		imshow("dst", dst);
		waitKey();
    } catch (const char *str) {
        cout << str << endl;
    }
    return 0;
}
