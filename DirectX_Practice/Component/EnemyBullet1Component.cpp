#include "EnemyBullet1Component.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"

EnemyBullet1Component::EnemyBullet1Component(Actor* onwer, Sprite* playerSprite) :
    Component(onwer),
    mSprite(nullptr),
    mPlayerSprite(playerSprite),
    mE2P(Vector2::zero),
    BULLET_SPEED(4.f),
    MAX_SCALE(0.5f),
    MIN_SCALE(0.2f),
    ROTATE_SPEED(8.f),
    SCALING_SPEED(0.03f),
    mScaleCounter(0) {
}

EnemyBullet1Component::~EnemyBullet1Component() = default;

void EnemyBullet1Component::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();

    mE2P = mPlayerSprite->getPosition() - mSprite->getPosition();
    mE2P.Normalize();
}

void EnemyBullet1Component::update() {
    move();
    destroy();
}

void EnemyBullet1Component::move() {
    mSprite->translate(mE2P * BULLET_SPEED * AvoidancePlayerActor::slow());

    mSprite->rotate(ROTATE_SPEED * AvoidancePlayerActor::slow());

    mScaleCounter += SCALING_SPEED * 100 * AvoidancePlayerActor::slow();
    mSprite->setScale(Math::sin(mScaleCounter * Math::deg2Rad) * MAX_SCALE, true);
    if (mScaleCounter >= 180 - MIN_SCALE * 100) {
        mScaleCounter = MIN_SCALE * 100;
    }
}

void EnemyBullet1Component::destroy() {
    auto lengthX = Math::abs(mSprite->getPosition().x);
    auto lengthY = Math::abs(mSprite->getPosition().y);
    if (lengthX > Game::WINDOW_WIDTH + 100 || lengthY > Game::WINDOW_HEIGHT + 100) {
        Actor::destroy(mOwner);
    }
}
