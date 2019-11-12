#include "EnemyActor.h"
#include "PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/EnemyMoveComponent.h"
#include "../Component/SpriteComponent.h"
#include <cassert>

EnemyActor::EnemyActor(PlayerActor* player, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mEnemyMove(new EnemyMoveComponent(this, player)),
    mSprite(new SpriteComponent(this, "cute_cat_illust_3737.png", Vector2(830.f, 800.f), 0.6f)) {
}

EnemyActor::~EnemyActor() = default;

void EnemyActor::updateActor() {
}

void EnemyActor::drawActor() const {
}
