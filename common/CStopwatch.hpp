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
  // �R���X�g���N�^
  CStopwatch() : mTotalElapsedTime(0.0) {}

  //-------------------------------------------------------------------
  // �^�C�}�[�Ԋu�̌v�����~���āA�o�ߎ��Ԃ��[���Ƀ��Z�b�g���܂��B
  void Reset() { mTotalElapsedTime = 0.0; }

  //-------------------------------------------------------------------
  // �Ԋu�̌o�ߎ��Ԃ̌v�����J�n�܂��͍ĊJ���܂��B
  void Start() { ftime((timeb *)(&mStartTime)); }

  //-------------------------------------------------------------------
  // �Ԋu�̌o�ߎ��Ԃ̌v�����~���܂��B
  float Stop() {
    struct timeb stopTime;

    ftime((timeb *)(&stopTime));
    float elapsedTime =
        static_cast<float>(stopTime.time - mStartTime.time) +
        static_cast<float>(stopTime.millitm - mStartTime.millitm) / 1000.0f;

    return elapsedTime;
  }

  //-------------------------------------------------------------------
  // �Ԋu�̌o�ߎ��Ԃ̌v�����~���A����܂ł̎��Ԃ�ώZ���܂��B
  void StopAndAccumTime() { mTotalElapsedTime += Stop(); }

  //-------------------------------------------------------------------
  // �o�ߎ��Ԃ��擾���܂��B
  float getElapsedTime() { return mTotalElapsedTime; }
};

#endif /* __CSTOPWATCHHPP__ */
