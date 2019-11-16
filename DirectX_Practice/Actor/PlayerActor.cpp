#include "PlayerActor.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mHP(new HitPointComponent(this, 100)),
    mPlayerMove(new PlayerMoveComponent(this)),
    mSprite(new SpriteComponent(this, "kuppa.png", Vector2(548.f, 599.f), 0.5f)) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "EnemyBullet") {
            continue;
        }
        auto damage = c->getOwner()->getComponentManager()->getComponent<DamageComponent>();
        mHP->takeDamage(damage->damage());
    }
}

void PlayerActor::drawActor() const {
}
