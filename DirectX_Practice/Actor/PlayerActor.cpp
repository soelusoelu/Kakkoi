#include "PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mPlayerMove(new PlayerMoveComponent(this)),
    mSprite(new SpriteComponent(this, "kuppa.png", Vector2(548.f, 599.f), 0.5f)) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
}
