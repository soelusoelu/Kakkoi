#include "PlayerMoveComponent.h"
#include "TransformComponent.h"
#include "../Actor/Actor.h"
#include "../Utility/Input.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mSpeed(0.3f) {
}

void PlayerMoveComponent::update() {
    int speed = Input::vertical();
    if (!Math::nearZero(speed)) {
        mOwner->getTransform()->translete(mOwner->getTransform()->forward() * mSpeed);
    }

    int rot = Input::horizontal();
    if (!Math::nearZero(rot)) {
        mOwner->getTransform()->rotate(Vector3::up, rot);
    }
}
