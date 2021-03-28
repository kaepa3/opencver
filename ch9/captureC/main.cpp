#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

static UMat makeMask(int w, int h) {
  Size sz(w, h);
  UMat mask(sz, CV_8UC1, Scalar());
  Point p0 = Point(w / 4., h / 4);
  Point p1 = Point(w * 3 / 4., h * 3 / 4);
  rectangle(mask, p0, p1, Scalar(255), -1);
  return mask;
}
int main(int argc, char *argv[]) {
    try
    {
        VideoCapture capture(0);
        if (!capture.open(0))
            throw "camera not found!";

        int width = static_cast<int>(capture.get(CAP_PROP_FRAME_WIDTH));
        int height = static_cast<int>(capture.get(CAP_PROP_FRAME_HEIGHT));
        cout << "frame size = " << width << " x " << height << endl;

        double fps = capture.get(CAP_PROP_FPS);
        fps = fps > 0.0 ? fps : 30.0;
        VideoWriter save("dst.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),
            fps, Size(width, height), true);
        if (!save.isOpened())
            throw "VideoWriter failed to open!";

        const string wName = "camera";
        UMat src;
        namedWindow(wName, WINDOW_AUTOSIZE);
        while (true)
        {
            capture >> src;

            imshow(wName, src);

            save << src;

            if (waitKey(1) >= 0) break;
        }
    }
    catch (const char* str)
    {
        cerr << str << endl;
    }
    return 0;
}
