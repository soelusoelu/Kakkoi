#include "PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mPlayerMove(new PlayerMoveComponent(this)),
    mSprite(new SpriteComponent(this, "kuppa.png", Vector2(548.f, 599.f), 0.5f)),
    mHp(100) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "EnemyBullet") {
            continue;
        }

        c->getOwner()->attack(&mHp);
        mHp = Math::Max(mHp, 0);
    }
}

void PlayerActor::drawActor() const {
}

void PlayerActor::attack(int* hp) {
}

int PlayerActor::hp() const {
    return mHp;
}
