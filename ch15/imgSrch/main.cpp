
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../../Cbmp/Cbmp.h"
#include "../../common/CStopwatch.hpp"

using namespace std;

#pragma pack(push, 1)

typedef struct {
    int smlHeight;
    int smlWidth;
    int bigRowPitch;
    int smlRowPitch;
    int pixelPitch;
    int sumArrayWidth;
    int sumArrayHeight;
} paramType;
#pragma pack(pop)

void search(const int x, const int y, const paramType *p,
            const unsigned char *inBigImg, const unsigned char *inSmlImg,
            int *sumArray) {
    int bigOffset = (y * p->bigRowPitch) + (x * p->pixelPitch);
    int smlOffset = 0;
    int sum = 0;

    for (int dy = 0; dy < p->smlHeight; dy++) {
        for (int dx = 0; dx < (p->smlWidth) * (p->pixelPitch); dx++) {
            sum += abs(inBigImg[bigOffset + dx] - inSmlImg[smlOffset + dx]);
        }
        bigOffset += (p->bigRowPitch);
        smlOffset += (p->smlRowPitch);
    }
    sumArray[y * p->sumArrayWidth + x] = sum;
}

static void search(const Cbmp bmp[]) {
    int diff = INT_MAX, xPos = 0, yPos = 0;
    paramType param;

    param.smlHeight = bmp[1].mAbsHeight;
    param.smlWidth = bmp[1].mPdib->biWidth;
    param.bigRowPitch = bmp[0].mRowPitch;
    param.smlRowPitch = bmp[1].mRowPitch;
    param.pixelPitch = bmp[0].mPixelPitch;
    param.sumArrayHeight = bmp[0].mAbsHeight - param.smlHeight + 1;
    param.sumArrayWidth = bmp[0].mPdib->biWidth - param.smlWidth + 1;

    int *sumArray = new int[param.sumArrayHeight * param.sumArrayWidth];

    for (int y = 0; y < param.sumArrayHeight; y++) {
        for (int x = 0; x < param.sumArrayWidth; x++) {
            search(x, y, &param, bmp[0].mPbitmap, bmp[1].mPbitmap, sumArray);
        }
    }

    for (int y = 0; y < param.sumArrayHeight; y++) {
        for (int x = 0; x < param.sumArrayWidth; x++) {
            if (sumArray[y * param.sumArrayWidth + x] < diff) {
                diff = sumArray[y * param.sumArrayWidth + x];
                yPos = y;
                xPos = x;
            }
        }
    }

    delete[] sumArray;

    if (bmp[1].mPdib->biHeight > 0) {
        yPos = bmp[0].mAbsHeight - yPos - bmp[1].mAbsHeight;
    }

    cout << "pos, x=" << xPos << " y=" << yPos << ", diff=" << diff << endl;
}

int evalBmp(const Cbmp bmp[]) {

    cout << "refImage =" << bmp[0].getWidth() << " x " << bmp[0].getHeight()
         << ", " << bmp[0].getBitsPerPixcel() << "/ pixel" << endl;

    cout << "findImage =" << bmp[1].getWidth() << " x " << bmp[1].getHeight()
         << ", " << bmp[1].getBitsPerPixcel() << "/ pixel" << endl;

    if (bmp[0].mPdib->biWidth < bmp[1].mPdib->biWidth ||
        bmp[0].mAbsHeight < bmp[1].mAbsHeight) {
        throw "image size error";
    }

    if ((bmp[0].mPdib->biHeight < 0 && bmp[1].mPdib->biHeight > 0) ||
        (bmp[0].mPdib->biHeight > 0 && bmp[1].mPdib->biHeight < 0)) {
        throw "grid y error";
    }

    if (bmp[0].mPixelPitch != bmp[1].mPixelPitch) {
        throw "bit/pixel error";
    }

    if (bmp[0].getBitsPerPixcel() != 24 && bmp[0].getBitsPerPixcel() != 32) {
        throw "24/32bits per pixel";
    }
    return 0;
}
int main(int argc, char *argv[]) {
    try {

        CStopwatch sw;
        Cbmp bmp[2];

        bmp[0].loadFromFile("../../images/base.bmp");
        bmp[1].loadFromFile("../../images/crop.bmp");

        evalBmp(bmp);
        sw.Start();
        search(bmp);
        sw.StopAndAccumTime();
        cout << " elasped time = " << sw.getElapsedTime() << endl;
    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}
