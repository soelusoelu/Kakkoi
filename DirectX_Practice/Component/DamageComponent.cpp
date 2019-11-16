#include "DamageComponent.h"

DamageComponent::DamageComponent(Actor* onwer, int damage) :
    Component(onwer),
    mDamage(damage) {
}

DamageComponent::~DamageComponent() = default;

void DamageComponent::update() {
}

int DamageComponent::damage() const {
    return mDamage;
}

void DamageComponent::setDamage(int set) {
    mDamage = set;
}
