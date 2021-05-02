#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace cv;
using namespace std;

struct eventParam_t {
    Point org;
    Rect rect;
    bool mouseDown;

    String iName;
    Mat src;
    Mat dst;
};
//-------------------------------------------------------------------
void onMouseEvent(int event, int x, int y, int flags, void *uData) {
    eventParam_t *ev = static_cast<eventParam_t *>(uData);

    int width = abs(ev->org.x - x);
    int height = abs(ev->org.y - y);

    switch (event) {
    case EVENT_LBUTTONDOWN:
        ev->mouseDown = true;
        ev->org = Point(x, y);
        ev->rect = Rect(ev->org.x, ev->org.y, 0, 0);
        ev->src.copyTo(ev->dst);
        imshow(ev->iName, ev->dst);
        break;
    case EVENT_MOUSEMOVE:
        if (!ev->mouseDown)
            break;

        ev->rect.x = ev->org.x > x ? x : ev->rect.x;
        ev->rect.y = ev->org.y > y ? y : ev->rect.y;

        ev->rect = Rect(ev->rect.x, ev->rect.y, width, height);
        ev->src.copyTo(ev->dst);
        rectangle(ev->dst, ev->rect, Scalar(255));
        imshow(ev->iName, ev->dst);
        break;
    case EVENT_LBUTTONUP:
        ev->mouseDown = false;
        break;
    }
}

//-------------------------------------------------------------------
Rect adjRect(Rect rect, Size size) {
    Rect newRect = rect;
    if (newRect.x < 0) {
        newRect.width = rect.width + rect.x;
        newRect.x = 0;
    }
    if (newRect.y < 0) {
        newRect.height = rect.height + rect.y;
        newRect.y = 0;
    }
    if (newRect.x + newRect.width > size.width) {
        newRect.width = size.width - newRect.x;
    }
    if (newRect.y + newRect.height > size.height) {
        newRect.height = size.height - newRect.y;
    }
    return newRect;
}

//-------------------------------------------------------------------
void usage() {
    cout << "usage" << endl;
    cout << "    c: cut" << endl;
    cout << "    q: quit" << endl;
}

//-------------------------------------------------------------------
// main
int main(int argc, char *argv[]) {
    try {
        eventParam_t ev = {Point(0, 0), Rect(0, 0, 0, 0), false};

        if (argc < 2) {
            throw "no parameter";
        }

        ev.iName = argv[1];
        ev.src = imread(ev.iName);
        if (ev.src.empty()) {
            throw "no input file.";
        }

        usage();

        imshow(ev.iName, ev.src);

        setMouseCallback(ev.iName, onMouseEvent, (void *)&ev);
        while (1) {
            int key = waitKey(1);
            if (key == 'Q' || key == 'q')
                break;
            if (key == 'C' || key == 'c') {
                if (ev.rect.width == 0 || ev.rect.height == 0) {
                    cout << "no rect" << endl;
                    continue;
                }

                Rect tempRect = adjRect(ev.rect, ev.src.size());
                Mat dst(ev.src, tempRect);
                imwrite("cutter.jpg", dst);
                destroyWindow("dst");
                imshow("dst", dst);
            }
        }
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
