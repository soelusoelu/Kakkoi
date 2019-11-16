#include "HitPointComponent.h"
#include "CircleCollisionComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Utility/Math.h"

HitPointComponent::HitPointComponent(Actor* onwer, int hp) :
    Component(onwer),
    mHP(hp),
    DEFAULT_HP(hp),
    mCircle() {
}

HitPointComponent::~HitPointComponent() = default;

void HitPointComponent::start() {
    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
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
