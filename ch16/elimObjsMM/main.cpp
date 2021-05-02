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
    Mat intrim;
    Mat areaFixed;
    Mat dst;

    vector<Rect> list;
};
Mat redraw(vector<Rect> list, Mat src) {
    Mat mat;
    src.copyTo(mat);
    vector<Rect>::const_iterator it = list.begin();
    for (; it != list.end(); ++it) {
        rectangle(mat, *it, Scalar(255));
    }
    return mat;
}
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
        ev->areaFixed.copyTo(ev->intrim);
        imshow(ev->iName, ev->intrim);
        break;
    case EVENT_MOUSEMOVE:
        if (!ev->mouseDown)
            break;

        ev->rect.x = ev->org.x > x ? x : ev->rect.x;
        ev->rect.y = ev->org.y > y ? y : ev->rect.y;

        ev->rect = Rect(ev->rect.x, ev->rect.y, width, height);
        ev->areaFixed.copyTo(ev->intrim);
        rectangle(ev->intrim, ev->rect, Scalar(255));
        imshow(ev->iName, ev->intrim);
        break;
    case EVENT_LBUTTONUP:
        ev->intrim.copyTo(ev->areaFixed);
        ev->list.push_back(ev->rect);
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
    cout << "    e: eliminate objes" << endl;
    cout << "    u: undo" << endl;
    cout << "    l: list rectangle" << endl;
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

        ev.src.copyTo(ev.areaFixed);
        setMouseCallback(ev.iName, onMouseEvent, (void *)&ev);
		cout << "into loop" << endl;
        while (1) {
            int key = waitKey(1);
            if (key == 'Q' || key == 'q')
                break;
            if (key == 'U' || key == 'u') {
                if (ev.list.empty())
                    continue;

                ev.list.pop_back();
                ev.areaFixed = redraw(ev.list, ev.src);
                imshow(ev.iName, ev.areaFixed);
            }
            if ((key == 'L' || key == 'l') && !ev.list.empty()) {
                cout << "list:" << endl;
                vector<Rect>::const_iterator it = ev.list.begin();
                for (; it != ev.list.end(); ++it) {
                    cout << " Rect(" << it->x << ", " << it->y << ", "
                         << it->width << ", " << it->height << ")" << endl;
                }
            }
            if ((key == 'E' || key == 'e') && !ev.list.empty()) {
                Mat mask(ev.src.size(), CV_8UC1, Scalar(0));

                vector<Rect>::const_iterator it = ev.list.begin();
                for (; it != ev.list.end(); ++it) {
                    Rect temp =
                        adjRect(Rect(it->x, it->y, it->width, it->height),
                                ev.src.size());
                    rectangle(mask, temp, Scalar(255), FILLED);
                }
                inpaint(ev.src, mask, ev.dst, 1, INPAINT_TELEA);
                destroyWindow("dst");
                imshow("dst", ev.dst);
            }
        }
		cout << "end loop" << endl;
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
