#include "PlayerActor.h"
#include "../Component/MeshComponent.h"
#include "../Component/PlayerMoveComponent.h"
#include "../Component/SphereCollisionComponent.h"
#include "../Component/TransformComponent.h"

PlayerActor::PlayerActor(const char* tag) :
    Actor(tag),
    mPlayerMove(new PlayerMoveComponent(this)),
    mMesh(new MeshComponent(this, "LINK.obj")),
    mSphere(new SphereCollisionComponent(this)) {
    mTransform->setScale(0.6f);
}

PlayerActor::~PlayerActor() = default;

void PlayerActor::updateActor() {
}

void PlayerActor::drawActor() const {
    mMesh->draw();
    mSphere->drawCollision();
}
