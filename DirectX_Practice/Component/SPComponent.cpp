#include "SPComponent.h"
#include "../Utility/Math.h"

SPComponent::SPComponent(Actor* onwer) :
    Component(onwer),
    mSP(0),
    mCurrentGaugeCount(0),
    ONE_GAUGE(100),
    GAUGE_COUNT(3),
    MAX_SP(ONE_GAUGE * GAUGE_COUNT) {
}

SPComponent::~SPComponent() = default;

void SPComponent::update() {
    mCurrentGaugeCount = mSP / (ONE_GAUGE + 1);
}

void SPComponent::set(int sp) {
    mSP = sp;
}

bool SPComponent::use(int sp) {
    mSP -= sp;
    mSP = Math::Max(mSP, 0);
    return true;
}

void SPComponent::heal(int sp) {
    mSP += sp;
    mSP = Math::Min<int>(mSP, MAX_SP);
}

int SPComponent::sp() const {
    return mSP;
}

const int SPComponent::maxSP() const {
    return MAX_SP;
}

const int SPComponent::getOneGauge() const {
    return ONE_GAUGE;
}

int SPComponent::getCurrentGaugeCount() const {
    return mCurrentGaugeCount;
}
