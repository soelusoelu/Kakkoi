#include "HitPointComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Utility/Math.h"

HitPointComponent::HitPointComponent(Actor* onwer, int hp) :
    Component(onwer),
    mHP(hp),
    DEFAULT_HP(hp) {
}

HitPointComponent::~HitPointComponent() = default;

void HitPointComponent::start() {
}

void HitPointComponent::update() {
}

void HitPointComponent::takeDamage(int damage) {
    mHP -= damage;
    mHP = Math::Max<int>(mHP, 0);
}

void HitPointComponent::takeHeal(int heal) {
    mHP += heal;
}

int HitPointComponent::hp() const {
    return mHP;
}
