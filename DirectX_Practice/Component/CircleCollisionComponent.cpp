#include "CircleCollisionComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"
#include <cassert>

CircleCollisionComponent::CircleCollisionComponent(Actor* onwer) :
    Component(onwer),
    mCircle(nullptr),
    mSprite(nullptr) {
}

CircleCollisionComponent::~CircleCollisionComponent() = default;

void CircleCollisionComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    assert(mSprite);

    mCircle = std::make_shared<Circle>(mSprite->getPosition() + mSprite->getPivot(), mSprite->getSize().x - mSprite->getPivot().x);
}

void CircleCollisionComponent::update() {
    mCircle->set(mSprite->getPosition() + mSprite->getPivot(), mSprite->getSize().x - mSprite->getPivot().x);
}
