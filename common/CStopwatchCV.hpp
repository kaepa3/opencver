//
//
//--------------------------------------------------------------------------

#ifndef __CSTOPWATCHCVHPP__
#define __CSTOPWATCHCVHPP__

//-------------------------------------------------------------------
#include <opencv2/core/core.hpp>

//-------------------------------------------------------------------
class CStopwatch
{
private:
    double mFrequency;
    double mTotalElapsedTime;
    int64  mStartTick;

public:
//-------------------------------------------------------------------
// コンストラクタ
CStopwatch::CStopwatch()
: mTotalElapsedTime(0.0)
{
    mFrequency = cv::getTickFrequency();
}

//-------------------------------------------------------------------
// タイマー間隔の計測を停止して、経過時間をゼロにリセットします。
void
CStopwatch::Reset() { mTotalElapsedTime = 0.0; };

//-------------------------------------------------------------------
// 間隔の経過時間の計測を開始または再開します。
void
CStopwatch::Start() { mStartTick = cv::getTickCount(); }

//-------------------------------------------------------------------
// 間隔の経過時間の計測を停止します。
double
CStopwatch::Stop()
{
    int64 stopTick = cv::getTickCount();

    double elapsedTime = static_cast<double>(stopTick-mStartTick)
                                                        /mFrequency;

    return elapsedTime;
}

//-------------------------------------------------------------------
// 間隔の経過時間の計測を停止し、これまでの時間を積算します。
void
CStopwatch::StopAndAccumTime() { mTotalElapsedTime+=Stop(); }

//-------------------------------------------------------------------
// 経過時間を取得します。
double
CStopwatch::getElapsedTime() { return mTotalElapsedTime; }

};

#endif  /* __CSTOPWATCHCVHPP__ */
