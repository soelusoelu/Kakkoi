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
    void setOverLimit();

private:
    int mCurrentTime;
    int mLimitTime;
    bool mIsOverLimit;
};
