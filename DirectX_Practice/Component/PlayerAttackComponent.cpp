#include "PlayerAttackComponent.h"
#include "../Actor/Actor.h"

PlayerAttackComponent::PlayerAttackComponent(Actor* onwer) :
    Component(onwer),
    mCurrentTime(0),
    DESTROY_TIME(10) {
}

PlayerAttackComponent::~PlayerAttackComponent() = default;

void PlayerAttackComponent::update() {
    mCurrentTime++;
    if (mCurrentTime >= DESTROY_TIME) {
        Actor::destroy(mOwner);
    }
}
