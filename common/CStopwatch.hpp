//
//
//--------------------------------------------------------------------------

#ifndef __CSTOPWATCHHPP__
#define __CSTOPWATCHHPP__

//-------------------------------------------------------------------
#include <sys/timeb.h>
#include <time.h>

//-------------------------------------------------------------------
class CStopwatch {
private:
  struct timeb mStartTime;
  float mTotalElapsedTime;

public:
  //-------------------------------------------------------------------
  // コンストラクタ
  CStopwatch() : mTotalElapsedTime(0.0) {}

  //-------------------------------------------------------------------
  // タイマー間隔の計測を停止して、経過時間をゼロにリセットします。
  void Reset() { mTotalElapsedTime = 0.0; }

  //-------------------------------------------------------------------
  // 間隔の経過時間の計測を開始または再開します。
  void Start() { ftime((timeb *)(&mStartTime)); }

  //-------------------------------------------------------------------
  // 間隔の経過時間の計測を停止します。
  float Stop() {
    struct timeb stopTime;

    ftime((timeb *)(&stopTime));
    float elapsedTime =
        static_cast<float>(stopTime.time - mStartTime.time) +
        static_cast<float>(stopTime.millitm - mStartTime.millitm) / 1000.0f;

    return elapsedTime;
  }

  //-------------------------------------------------------------------
  // 間隔の経過時間の計測を停止し、これまでの時間を積算します。
  void StopAndAccumTime() { mTotalElapsedTime += Stop(); }

  //-------------------------------------------------------------------
  // 経過時間を取得します。
  float getElapsedTime() { return mTotalElapsedTime; }
};

#endif /* __CSTOPWATCHHPP__ */
