#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../UI/Sprite.h"
#include "../Component/SpriteComponent.h"
#include "../Utility/Input.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mSprite(nullptr),
    mSpeed(2.f) {
}

void PlayerMoveComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setScale(0.25f);
}

void PlayerMoveComponent::update() {
    int vertical = Input::vertical();
    if (!Math::nearZero(vertical)) {
        mSprite->translate(Vector2(0.f, -vertical * mSpeed));
    }
}
