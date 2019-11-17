#include "Time.h"

Time::Time(float sec) :
    mCurrentTime(0),
    mLimitTime(sec * 60.f),
    mIsOverLimit(false) {
}

Time::~Time() = default;

void Time::update() {
    mCurrentTime++;

    if (mCurrentTime >= mLimitTime) {
        mIsOverLimit = true;
    }
}

void Time::reset() {
    mCurrentTime = 0;
    mIsOverLimit = false;
}

bool Time::isTime() const {
    return mIsOverLimit;
}

void Time::setLimitTime(float sec) {
    mLimitTime = sec * 60.f;
}

int Time::currentTimer() const {
    return mCurrentTime / 60;
}
