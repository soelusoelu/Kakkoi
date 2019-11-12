#include "EnemyBullet1Component.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"

EnemyBullet1Component::EnemyBullet1Component(Actor* onwer, Sprite* playerSprite) :
    Component(onwer),
    mSprite(nullptr),
    mPlayerSprite(playerSprite),
    mFirst(true),
    mE2P(Vector2::zero),
    BULLET_SPEED(2.f) {
}

EnemyBullet1Component::~EnemyBullet1Component() = default;

void EnemyBullet1Component::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
}

void EnemyBullet1Component::update() {
    if (mFirst) {
        mFirst = false;
        mE2P = mPlayerSprite->getPosition() - mSprite->getPosition();
        mE2P.Normalize();
    }
    mSprite->translate(mE2P * BULLET_SPEED);

    auto length = Math::abs(Game::WINDOW_WIDTH / 2.f - mSprite->getPosition().x);
    if (length > Game::WINDOW_WIDTH) {
        Actor::destroy(mOwner);
    }
}
