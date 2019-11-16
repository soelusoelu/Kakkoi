#include "EnemyActor.h"
#include "PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/EnemyMoveComponent.h"
#include "../Component/SpriteComponent.h"

EnemyActor::EnemyActor(PlayerActor* player, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mEnemyMove(new EnemyMoveComponent(this, player)),
    mSprite(new SpriteComponent(this, "cute_cat_illust_3737.png", Vector2(830.f, 800.f), 0.6f)),
    mHp(500) {
}

EnemyActor::~EnemyActor() = default;

void EnemyActor::updateActor() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "PlayerAttack") {
            return;
        }

        c->getOwner()->attack(&mHp);
    }
}

void EnemyActor::drawActor() const {
}

void EnemyActor::attack(int* hp) {
}

const int EnemyActor::hp() const {
    return mHp;
}
