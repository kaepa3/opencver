#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <string>

using namespace cv;
using namespace std;

inline bool x2small(const Point2f &left, const Point2f &right) {
    return left.x < right.x;
}

inline bool y2small(const Point2f &left, const Point2f &right) {
    return left.y < right.y;
}

inline bool y2big(const Point2f &left, const Point2f &right) {
    return left.y > right.y;
}

//-------------------------------------------------------------------
void usage() {
    cout << "usage" << endl;
    cout << "    f: flip image" << endl;
    cout << "    q: quit" << endl;
}

//-------------------------------------------------------------------
// main
int main(int argc, char *argv[]) {
    cout << "into main " << endl;
    try {
        Mat src, gray;
        int persWidth, persHeight;

        if (argc > 1) {
            src = imread(argv[1]);
            if (src.empty()) {
                throw "no image";
            }
        } else
            throw "no args";

        usage();

        persWidth = src.cols;
        persHeight = src.rows;
        if (argc == 4) {
            persWidth = stoi(argv[2]);
            persHeight = stoi(argv[3]);
        }
        cvtColor(src, gray, COLOR_RGB2GRAY);
        threshold(gray, gray, 200, 255, THRESH_BINARY);
        //threshold(gray, gray, 128, 255, THRESH_BINARY);
		
		imshow("threshold", gray);
		waitKey(0);
		
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(gray, contours, hierarchy, RETR_EXTERNAL,
                     CHAIN_APPROX_TC89_L1);

        int maxLevel = 0;
        Mat findContours = src.clone();
        for (int i = 0; i < contours.size(); i++) {
            drawContours(findContours, contours, i, Scalar_(255, 0, 0), 1,
                         LINE_AA, hierarchy, maxLevel);
        }
        imshow("findContours", findContours);

        Mat detectObjs = src.clone();
        maxLevel = 0;
        vector<vector<Point>> tmpContours;
        for (int i = 0; i < contours.size(); i++) {
            double a = contourArea(contours[i], false);
            if (a > 50 * 50) {
                vector<Point> approx;
                approxPolyDP(Mat(contours[i]), approx,
                             0.01 * arcLength(contours[i], true), true);
                if (approx.size() == 4) {
                    tmpContours.push_back(approx);
                    drawContours(detectObjs, tmpContours, 0, Scalar(0, 0, 255),
                                 1, LINE_AA, hierarchy, maxLevel);
                }
            }
        }
        imshow("detectObjs", detectObjs);
        vector<Point2f> sortContours;
        for (int i = 0; i < 4; i++) {
            sortContours.push_back((Point2f)tmpContours[0][i]);
        }
        sort(sortContours.begin(), sortContours.end(), x2small);
        sort(sortContours.begin(), sortContours.begin() + 2, y2small);
        sort(sortContours.begin() + 2, sortContours.end(), y2big);

        Point2f psrc[4];
        for (int i = 0; i < 4; i++) {
            psrc[i] = (Point2f)sortContours[i];
        }
        Point2f pdst[] = {
            {0.0f, 0.0f},
            {0.0f, (float)(persHeight - 1)},
            {(float)(persWidth - 1), (float)(persHeight - 1)},
            {(float)(persWidth - 1), 0.0f},
        };

        Mat persMatrix = getPerspectiveTransform(psrc, pdst);
        Mat pers(persHeight, persWidth, CV_8UC3);
        warpPerspective(src, pers, persMatrix, pers.size(), INTER_LINEAR);

        imshow("src", src);
        imshow("pers", pers);

        while (1) {
            int key = waitKey(1);
            if (key == 'q') {
                break;
            }
            if (key == 'f') {
                Point2f tmpDst = pdst[3];
                for (int i = 3; i > 0; i--) {
                    pdst[i] = pdst[i - 1];
                }
                pdst[0] = tmpDst;
                persMatrix = getPerspectiveTransform(psrc, pdst);
                warpPerspective(src, pers, persMatrix, pers.size(),
                                INTER_LINEAR);

				imshow("pers", pers);
            }
        }
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
