#include "PlayerActor.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/TransformComponent.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mPlayerMove(new PlayerMoveComponent(this)) {
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
}
