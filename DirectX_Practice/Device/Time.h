#pragma once

class Time {
public:
    Time(float sec);
    ~Time();
    void update();
    void reset();
    bool isTime() const;
    void setLimitTime(float sec);
    int currentTimer() const;

private:
    int mCurrentTime;
    int mLimitTime;
    bool mIsOverLimit;
};
