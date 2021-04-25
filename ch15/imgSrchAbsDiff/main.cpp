#include "../../common/CStopwatch.hpp"
#include "../../common/common.h"

using namespace cv;
using namespace std;

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

//-------------------------------------------------------------------
// search image
template <typename T_n> static float search(const T_n mat[], Point *pos) {
    T_n dst;
    double fMin = FLT_MAX;

    // srch
    int srchCols = mat[0].cols - mat[1].cols + 1;
    int srchRows = mat[0].rows - mat[1].rows + 1;
    for (int y = 0; y < srchRows; y++) {
        for (int x = 0; x < srchCols; x++) {
            Rect roi = Rect(x, y, mat[1].cols, mat[1].rows);
            T_n tgtRoi(mat[0], roi);

            absdiff(tgtRoi, mat[1], dst);
            double r = sum(dst)[0];

            if (fMin > r) {
                fMin = r;
                pos->y = y;
                pos->x = x;
            }
        }
    }
    return (float)fMin;
}

//-------------------------------------------------------------------
// main
int main(int argc, char *argv[]) {
    try {
        CStopwatch sw;
        Mat src[2];
        // UMat src[2];
        Point pos = Point(-1, -1);

        if (argc < 3)
            throw "few parameters.";

        imread(argv[1], IMREAD_GRAYSCALE).copyTo(src[0]);
        imread(argv[2], IMREAD_GRAYSCALE).copyTo(src[1]);

        evalMat(src);

        sw.Start();

        float r = search(src, &pos); // search image

        sw.StopAndAccumTime();

        cout << "elapsed time = " << sw.getElapsedTime() << endl;
        cout << "result = " << r << endl;

        drawPos(argv, pos);

        if (argc == 3)
            waitKey(0);
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
