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
// �R���X�g���N�^
CStopwatch::CStopwatch()
: mTotalElapsedTime(0.0)
{
    mFrequency = cv::getTickFrequency();
}

//-------------------------------------------------------------------
// �^�C�}�[�Ԋu�̌v�����~���āA�o�ߎ��Ԃ��[���Ƀ��Z�b�g���܂��B
void
CStopwatch::Reset() { mTotalElapsedTime = 0.0; };

//-------------------------------------------------------------------
// �Ԋu�̌o�ߎ��Ԃ̌v�����J�n�܂��͍ĊJ���܂��B
void
CStopwatch::Start() { mStartTick = cv::getTickCount(); }

//-------------------------------------------------------------------
// �Ԋu�̌o�ߎ��Ԃ̌v�����~���܂��B
double
CStopwatch::Stop()
{
    int64 stopTick = cv::getTickCount();

    double elapsedTime = static_cast<double>(stopTick-mStartTick)
                                                        /mFrequency;

    return elapsedTime;
}

//-------------------------------------------------------------------
// �Ԋu�̌o�ߎ��Ԃ̌v�����~���A����܂ł̎��Ԃ�ώZ���܂��B
void
CStopwatch::StopAndAccumTime() { mTotalElapsedTime+=Stop(); }

//-------------------------------------------------------------------
// �o�ߎ��Ԃ��擾���܂��B
double
CStopwatch::getElapsedTime() { return mTotalElapsedTime; }

};

#endif  /* __CSTOPWATCHCVHPP__ */
