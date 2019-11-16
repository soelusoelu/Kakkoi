#include "PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
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

        mHP->takeDamage(10);
    }
}

void PlayerActor::drawActor() const {
}
