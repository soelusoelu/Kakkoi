#include "EnemyBullet2Component.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"

EnemyBullet2Component::EnemyBullet2Component(Actor* owner, Sprite* playerSprite, float rotation) :
    Component(owner),
    mSprite(nullptr),
    mPlayerSprite(playerSprite),
    mVelocity(Vector2::zero),
    ROTATION(rotation),
    BULLET_SPEED(7.f) {
    auto x = Math::cos(ROTATION * Math::deg2Rad);
    auto y = Math::sin(ROTATION * Math::deg2Rad);
    mVelocity = Vector2(x, y);
}

EnemyBullet2Component::~EnemyBullet2Component() = default;

void EnemyBullet2Component::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setScale(0.1f);
}

void EnemyBullet2Component::update() {
    mSprite->translate(mVelocity * BULLET_SPEED * AvoidancePlayerActor::slow());
    destroy();
}

void EnemyBullet2Component::destroy() {
    auto lengthX = Math::abs(mSprite->getPosition().x);
    auto lengthY = Math::abs(mSprite->getPosition().y);
    if (lengthX > Game::WINDOW_WIDTH + 100 || lengthY > Game::WINDOW_HEIGHT + 100) {
        Actor::destroy(mOwner);
    }
}
