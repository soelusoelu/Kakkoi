#include "PlayerAttackComponent.h"
#include "../Actor/Actor.h"
#include "../Device/Time.h"

PlayerAttackComponent::PlayerAttackComponent(Actor* onwer) :
    Component(onwer),
    mTimer(std::make_unique<Time>(0.16f)) {
}

PlayerAttackComponent::~PlayerAttackComponent() = default;

void PlayerAttackComponent::update() {
    mTimer->update();
    if (mTimer->isTime()) {
        Actor::destroy(mOwner);
    }
}
