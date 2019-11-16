#include "EnemyActor.h"
#include "PlayerActor.h"
#include "ComponentManagementOfActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/EnemyMoveComponent.h"
#include "../Component/SpriteComponent.h"

EnemyActor::EnemyActor(PlayerActor* player, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mHP(new HitPointComponent(this, 500)),
    mEnemyMove(new EnemyMoveComponent(this, player)),
    mSprite(new SpriteComponent(this, "cute_cat_illust_3737.png", Vector2(830.f, 800.f), 0.6f)) {
}

EnemyActor::~EnemyActor() = default;

void EnemyActor::updateActor() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "PlayerAttack") {
            return;
        }

        auto damage = c->getOwner()->getComponentManager()->getComponent<DamageComponent>();
        mHP->takeDamage(damage->damage());
    }
}

void EnemyActor::drawActor() const {
}
