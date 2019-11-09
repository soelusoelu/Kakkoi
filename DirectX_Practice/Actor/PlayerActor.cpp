#include "PlayerActor.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SpriteComponent.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mPlayerMove(new PlayerMoveComponent(this)),
    mSprite(new SpriteComponent(this, "kuppa.png", Vector2(548.f, 599.f), 0.2f)) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
}
