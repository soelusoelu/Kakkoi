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
    mE2P(Vector2::zero),
    BULLET_SPEED(4.f),
    COMPLEMENT_VALUE(0.2f),
    MAX_SCALE(0.5f),
    MIN_SCALE(0.2f),
    ROTATE_SPEED(8.f),
    SCALING_SPEED(0.03f) {
}

EnemyBullet1Component::~EnemyBullet1Component() = default;

void EnemyBullet1Component::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setScale(MAX_SCALE);

    auto p = mPlayerSprite->getPosition();
    auto e = mSprite->getPosition();
    mE2P = p - e;
    mE2P.Normalize();
}

void EnemyBullet1Component::update() {
    move();
    destroy();
}

void EnemyBullet1Component::move() {
    mSprite->translate(mE2P * BULLET_SPEED);

    mSprite->rotate(ROTATE_SPEED);

    static bool is = true;
    if (is) {
        mSprite->setScale(mSprite->getScale().x - SCALING_SPEED, true);
        if (mSprite->getScale().x <= MIN_SCALE) {
            is = false;
        }
    } else {
        mSprite->setScale(mSprite->getScale().x + SCALING_SPEED, true);
        if (mSprite->getScale().x >= MAX_SCALE) {
            is = true;
        }
    }
}

void EnemyBullet1Component::destroy() {
    auto lengthX = Math::abs(mSprite->getPosition().x);
    auto lengthY = Math::abs(mSprite->getPosition().y);
    if (lengthX > Game::WINDOW_WIDTH + 100 || lengthY > Game::WINDOW_HEIGHT + 100) {
        Actor::destroy(mOwner);
    }
}
