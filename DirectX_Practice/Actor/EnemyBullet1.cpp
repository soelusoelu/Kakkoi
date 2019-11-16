#include "EnemyBullet1.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/EnemyBullet1Component.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

EnemyBullet1::EnemyBullet1(Sprite* playerSprite, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mEnemyBullet(new EnemyBullet1Component(this, playerSprite)),
    mSprite(new SpriteComponent(this, "effect.jpg", Vector2(400.f, 400.f), 0.2f)),
    mDamagePoint(10) {
}

EnemyBullet1::~EnemyBullet1() = default;

void EnemyBullet1::updateActor() {
}

void EnemyBullet1::drawActor() const {
}

void EnemyBullet1::attack(int* hp) {
    *hp -= mDamagePoint;
}
