#include "EnemyBullet2.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/EnemyBullet2Component.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

EnemyBullet2::EnemyBullet2(Sprite* enemySprite, float rotation, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, 50)),
    mEnemyBullet(new EnemyBullet2Component(this, enemySprite, rotation)),
    mSprite(new SpriteComponent(this, "fire.png", Vector2(64.f, 64.f), 0.2f)) {
}

EnemyBullet2::~EnemyBullet2() = default;

void EnemyBullet2::updateActor() {
}

void EnemyBullet2::drawActor() const {
}
