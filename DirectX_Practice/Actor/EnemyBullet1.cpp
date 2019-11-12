#include "EnemyBullet1.h"
#include "../Component/EnemyBullet1Component.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

EnemyBullet1::EnemyBullet1(Sprite* playerSprite, const char* tag) :
    Actor(tag),
    mEnemyBullet(new EnemyBullet1Component(this, playerSprite)),
    mSprite(new SpriteComponent(this, "effect.jpg", Vector2(400.f, 400.f), 0.2f)) {
    mSprite->getSprite()->setScale(0.5f, true);
}

EnemyBullet1::~EnemyBullet1() = default;

void EnemyBullet1::updateActor() {
}

void EnemyBullet1::drawActor() const {
}
