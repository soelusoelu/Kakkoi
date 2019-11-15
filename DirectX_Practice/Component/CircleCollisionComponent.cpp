#include "CircleCollisionComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Physics.h"
#include "../UI/Sprite.h"
#include <cassert>

CircleCollisionComponent::CircleCollisionComponent(Actor* onwer) :
    Component(onwer),
    mCircle(nullptr),
    mSprite(nullptr) {
}

CircleCollisionComponent::~CircleCollisionComponent() {
    Physics::remove(this);
}

void CircleCollisionComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    assert(mSprite);

    mCircle = std::make_shared<Circle>(
        mSprite->getPosition() + mSprite->getPivot(),
        mSprite->getSize().x * mSprite->getScale().x - mSprite->getPivot().x);

    Physics::add(this);
}

void CircleCollisionComponent::update() {
    mCircle->set(
        mSprite->getPosition() + mSprite->getPivot(),
        mSprite->getSize().x * mSprite->getScale().x - mSprite->getPivot().x
    );
}

std::shared_ptr<Circle> CircleCollisionComponent::getCircle() const {
    return mCircle;
}
