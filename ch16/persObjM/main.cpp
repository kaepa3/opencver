#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include <string>

using namespace cv;
using namespace std;

struct eventParam_t {
    vector<Point> contours;

    string iName;
    string pers;
    Mat src;
    Mat dst;
};

Mat redraw(vector<Point> list, Mat src) {
    Mat mat;
    int npt[1];
    Point point[1][4];
    const Point *ppt[] = {point[0]};

    src.copyTo(mat);

    npt[0] = (int)list.size();
    for (int i = 0; i < list.size(); i++) {
        point[0][i] = list[i];
    }
    polylines(mat, ppt, npt, 1, true, cv::Scalar(0, 0, 255), 1, 8);
    return mat;
}

inline bool x2small(const Point2f &left, const Point2f &right) {
    return left.x < right.x;
}

inline bool y2small(const Point2f &left, const Point2f &right) {
    return left.y < right.y;
}

inline bool y2big(const Point2f &left, const Point2f &right) {
    return left.y > right.y;
}

void sortPoint(vector<Point> contours) {
    sort(contours.begin(), contours.end(), x2small);
    sort(contours.begin(), contours.begin() + 2, x2small);
    sort(contours.begin() + 2, contours.end(), x2small);
}
void onMouseEvent(int event, int x, int y, int flags, void *uData) {
    eventParam_t *ev = static_cast<eventParam_t *>(uData);
    switch (event) {
    case EVENT_LBUTTONDOWN:
		cout << "ldown" <<endl;
        if (ev->contours.size() > 3)
            break;
        ev->contours.push_back(Point(x, y));
        if (ev->contours.size() == 4)
            sortPoint(ev->contours);

        ev->dst = redraw(ev->contours, ev->src);
        imshow(ev->iName, ev->dst);
        break;
    case EVENT_RBUTTONDOWN:
		cout << "rdown" <<endl;
        ev->contours.clear();
        ev->src.copyTo(ev->dst);
        destroyWindow(ev->pers);
        break;
    }
}
//-------------------------------------------------------------------
void usage() {
    cout << "usage" << endl;
    cout << "left  mouse button: four corner object" << endl;
    cout << "right mouse button: undo" << endl;
    cout << "p                 : perspective" << endl;
    cout << "f                 : flip image" << endl;
    cout << "q                 : quit" << endl;
}

//-------------------------------------------------------------------
// main
int main(int argc, char *argv[]) {
    cout << "into main " << endl;
    try {
        eventParam_t ev;
        int persWidth, persHeight;

        if (argc > 1) {
            ev.iName = argv[1];
            ev.src = imread(ev.iName);
            if (ev.src.empty())
                throw "no image";
        } else
            throw "no args";

        persWidth = ev.src.cols;
        persHeight = ev.src.rows;
        if (argc == 4) {
            persWidth = stoi(argv[2]);
            persHeight = stoi(argv[3]);
        }

        usage();

        Point2f pdst[] = {
            {0.0f, 0.0f},
            {0.0f, (float)(persHeight - 1)},
            {(float)(persWidth - 1), (float)(persHeight - 1)},
            {(float)(persWidth - 1), 0.0f},
        };
        Mat persMatrix;
        Mat pers(persHeight, persWidth, CV_8UC3);

        ev.dst = ev.src.clone();
        imshow(ev.iName, ev.dst);

        setMouseCallback(ev.iName, onMouseEvent, (void *)&ev);

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
                key = 'p';
            }
            if (key == 'p' && ev.contours.size() == 4) {
                Point2f psrc[] = {
                    (Point2f)ev.contours[0],
                    (Point2f)ev.contours[1],
                    (Point2f)ev.contours[2],
                    (Point2f)ev.contours[3],
                };
                persMatrix = getPerspectiveTransform(psrc, pdst);
                warpPerspective(ev.src, pers, persMatrix, pers.size(),
                                INTER_LINEAR);

                imshow(ev.pers, pers);
            }
        }
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
