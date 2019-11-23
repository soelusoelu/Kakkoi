#pragma once

#include "Component.h"

class Actor;

class SPComponent : public Component {
public:
    SPComponent(Actor* onwer);
    ~SPComponent();
    virtual void update() override;
    void set(int sp);
    bool use(int sp);
    void heal(int sp);
    int sp() const;
    const int maxSP() const;
    const int getOneGauge() const;
    int getCurrentGaugeCount() const;
    int computeGaugeCount(int sp);
    float spRate() const;

private:
    int mSP;
    int mCurrentGaugeCount;
    const int ONE_GAUGE;
    const int GAUGE_COUNT;
    const int MAX_SP;
};

