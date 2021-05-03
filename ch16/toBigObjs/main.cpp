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

        cout << "koko" << endl;
        cvtColor(src, gray, COLOR_RGB2GRAY);
        equalizeHist(gray, equalize);

        CascadeClassifier objDetector(argv[2]);
        vector<Rect> objs;
        objDetector.detectMultiScale(equalize, objs, 1.2, 2,
                                     CASCADE_SCALE_IMAGE, Size(50, 50));

        src.copyTo(dst);
        vector<Mat> srcobjs, dstobjs;

        cout << "soko" << endl;

        vector<Rect>::const_iterator it = objs.begin();
        for (; it != objs.end(); ++it) {
            Rect srcrect(it->x, it->y, it->width, it->height);
            Mat srcroi(src, srcrect);
            srcobjs.push_back(srcroi);

            int deltaW = it->width / 8;
            int deltaH = it->height / 8;

            Rect dstrect(it->x - deltaW, it->y - deltaH, it->width + deltaW * 2,
                         it->height + deltaH * 2);
            Mat dstroi(dst, dstrect);
            dstobjs.push_back(dstroi);
        }
        cout << "dedw" << endl;
        for (int i = 0; i < srcobjs.size(); i++) {
            resize(srcobjs[i], srcobjs[i],
                   Size(dstobjs[i].cols, dstobjs[i].rows));
        }
        cout << "fdsa" << endl;

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
