#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"

using namespace cv;
using namespace std;

Mat createCosMat(const int rows, const int cols);
Mat mulMat(const Mat mat, const Mat table);

// main
int main(int argc, char *argv[]) {
    try {
        if (argc < 3)
            throw "few params";

        Mat src, gray, equalize, dst;
        src = imread(argv[1]);
        if (src.empty())
            throw "empty image";

        cvtColor(src, gray, COLOR_RGB2GRAY);
        equalizeHist(gray, equalize);

        CascadeClassifier objDetector(argv[2]);
        vector<Rect> objs;
        objDetector.detectMultiScale(equalize, objs, 1.2, 2,
                                     CASCADE_SCALE_IMAGE, Size(50, 50));

        src.copyTo(dst);
        vector<Mat> srcobjs, dstobjs;


        vector<Rect>::const_iterator it = objs.begin();
        for (; it != objs.end(); ++it) {
            int deltaW = it->width / 8;
            int deltaH = it->height / 8;

            Rect srcrect(it->x - deltaW, it->y - deltaH, it->width + deltaW * 2,
                         it->height + deltaH * 2);
            Mat srcroi(src, srcrect);
            srcobjs.push_back(srcroi);

            Rect dstrect(it->x, it->y, it->width, it->height);
            Mat dstroi(dst, dstrect);
            dstobjs.push_back(dstroi);
        }
        for (int i = 0; i < srcobjs.size(); i++) {
            resize(srcobjs[i], srcobjs[i],
                   Size(dstobjs[i].cols, dstobjs[i].rows));
        }
        for (int i = 0; i < srcobjs.size(); i++) {
            Mat weightMat = createCosMat(srcobjs[i].rows, srcobjs[i].cols);
            Mat iWeightMat = Scalar::all(255) - weightMat;

            Mat srcWeight = mulMat(srcobjs[i], weightMat);
            Mat dstWeight = mulMat(dstobjs[i], iWeightMat);
            add(dstWeight, srcWeight, dstobjs[i]);
        }
        cout << "a" << endl;

        imshow("src", src);
        imshow("dst", dst);
        waitKey(0);

    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
