#include "SPComponent.h"
#include "../Utility/Math.h"

SPComponent::SPComponent(Actor* onwer, int sp) :
    Component(onwer),
    mSP(sp),
    MAX_SP(sp) {
}

SPComponent::~SPComponent() = default;

void SPComponent::update() {
}

void SPComponent::set(int sp) {
    mSP = sp;
}

bool SPComponent::use(int sp) {
    if (mSP - sp < 0) {
        return false;
    }
    mSP -= sp;
    return true;
}

void SPComponent::takeHeal(int sp) {
    mSP += sp;
    mSP = Math::Min<int>(mSP, MAX_SP);
}

int SPComponent::sp() const {
    return mSP;
}
