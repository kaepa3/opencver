#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"
#include <type_traits>
#include <vector>

using namespace cv;
using namespace std;

struct pos_t {
    float val;
    int x;
    int y;
};

class LessPos {
  public:
    bool operator()(const pos_t &a, const pos_t &b) { return a.val < b.val; }
};

class GraterPos {
  public:
    bool operator()(const pos_t &a, const pos_t &b) { return a.val > b.val; }
};

//-------------------------------------------------------------------
// evalation images
template <typename T_n> static void evalMat(const T_n mat[]) {
    cout << "検索先画像 = " << mat[0].cols << " x " << mat[0].rows << endl;
    cout << "探す画像   = " << mat[1].cols << " x " << mat[1].rows << endl;

    if (mat[0].cols < mat[1].cols || mat[0].rows < mat[1].rows)
        throw "元画像ファイルの幅や高さが探す画像より小さい.";
}

//-------------------------------------------------------------------
// show/write result
static void drawPos(char *argv[], const Point pos) {
    Mat big, sml;

    cout << "pos, x=" << pos.x << " y=" << pos.y << endl;

    imread(argv[1]).copyTo(big);
    imread(argv[2]).copyTo(sml);

    Point pos2 = Point(pos.x + sml.cols, pos.y + sml.rows);
    rectangle(big, pos, pos2, Scalar(0, 0, 255), 2);
    imwrite("result.jpg", big); // write images

    imshow("search image", sml);
    imshow("result image", big);
}

template <typename T_n>
static T_n cutTgtMat(const T_n mat[], const Point *pos, Point *offsetPos,
                       const int divider) {
    cout << "pos ->x = " << pos->x << endl;
    cout << "pos ->y = " << pos->y << endl;

    int marginX = divider * 2;
    int marginY = divider * 2;

    int srchX = max(0, pos->x - marginX);
    int srchY = max(0, pos->y - marginY);

    int width = mat[1].cols + marginX * 2 > mat[0].cols
                    ? srchX - mat[0].cols
                    : mat[1].cols + marginX * 2;

    int height = mat[1].rows + marginY * 2 > mat[0].rows
                     ? srchX - mat[0].rows
                     : mat[1].rows + marginY * 2;

    cout << "srchArea X = " << srchX << " - " << srchX + marginX * 2 << endl;
    cout << "srchArea Y = " << srchY << " - " << srchY + marginY * 2 << endl;
    cout << "width = " << width << endl;
    cout << "height= " << height << endl;

    offsetPos->x = srchX;
    offsetPos->y = srchY;

    Rect roi = Rect(srchX, srchY, width, height);
    T_n tgtRoi(mat[0], roi);
    return tgtRoi;
}
//-------------------------------------------------------------------
// search image
template <typename T_n> static void search(const T_n mat[], vector<pos_t> &vp) {
    pos_t srchPos;
    T_n dst;

    // srch
    int srchCols = mat[0].cols - mat[1].cols + 1;
    int srchRows = mat[0].rows - mat[1].rows + 1;
    for (int y = 0; y < srchRows; y++) {
        for (int x = 0; x < srchCols; x++) {
            Rect roi = Rect(x, y, mat[1].cols, mat[1].rows);
            T_n tgtRoi(mat[0], roi);

            absdiff(tgtRoi, mat[1], dst);

            srchPos.val = sum(dst)[0];
            srchPos.x = x;
            srchPos.y = y;

            vp.push_back(srchPos);
            sort(vp.begin(), vp.end(), LessPos());

            if (vp.size() > 5) {
                vp.erase(--vp.end());
            }
        }
    }
}

//-------------------------------------------------------------------
// main
int main(int argc, char *argv[]) {
    try {
        CStopwatch sw;
        Mat src[2], tSrc[2], cutSrc;
        // UMat src[2];
        Point pos = Point(-1, -1);

        if (argc < 3)
            throw "few parameters.";

        imread(argv[1], IMREAD_GRAYSCALE).copyTo(src[0]);
        imread(argv[2], IMREAD_GRAYSCALE).copyTo(src[1]);
        tSrc[0] = src[0].clone();
        tSrc[1] = src[1].clone();

        evalMat(src);

        int divider = 0;
        if (argc >= 4) {
            divider = stoi(argv[3]);
        }

        int minWidthHeight = 20;
        if (divider <= 1) {
            int shortSide = min(src[1].cols, src[1].rows);
            divider = shortSide / minWidthHeight;
        }
        cout << "divider = " << divider << endl;

        sw.Start();

        vector<pos_t> vp;
        resize(tSrc[0], src[0],
               Size(tSrc[0].cols / divider, tSrc[0].rows / divider));
        resize(tSrc[1], src[1],
               Size(tSrc[1].cols / divider, tSrc[1].rows / divider));
        search(src, vp);

        pos.y = vp.begin()->y * divider;
        pos.x = vp.begin()->x * divider;

        Point offsetPos;
        tSrc[0] = cutTgtMat(tSrc, &pos, &offsetPos, divider);

        search(tSrc, vp);

        sw.StopAndAccumTime();

        for (vector<pos_t>::const_iterator it = vp.begin(); it != vp.end();
             it++) {
            cout << "x=" << it->x + offsetPos.x << ", y=" << it->y + offsetPos.y
                        << ", val=" << it->val << endl;
        }
        cout << endl;

        cout << "elapsed time = " << sw.getElapsedTime() << endl;
        cout << "result = " << vp.begin()->val << endl;

        pos.y = offsetPos.y + vp.begin()->y;
        pos.x = offsetPos.x + vp.begin()->x;
        drawPos(argv, pos);

        if (argc == 5)
            waitKey(0);
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
