#include "AvoidancePlayerActor.h"
#include "../Component/AvoidanceComponent.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Renderer.h"
#include "../Device/Time.h"
#include "../UI/Sprite.h"

AvoidancePlayerActor::AvoidancePlayerActor(PlayerActor* player, const Vector2& position, const std::string& fileName, const Vector2& size, const Vector2& scale, const char* tag) :
    Actor(tag),
    mAvoidance(new AvoidanceComponent(this, player)),
    mCircle(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, fileName, size, 0.51f)) {
    auto s = mSprite->getSprite();
    s->setAlpha(0.f);
    s->setScale(scale);
    s->setPosition(position);
}

AvoidancePlayerActor::~AvoidancePlayerActor() = default;

void AvoidancePlayerActor::updateActor() {
}

void AvoidancePlayerActor::drawActor() const {
}

float AvoidancePlayerActor::slow() {
    return mSuccessedAvoidance ? mSlowRatio : 1.f;
}

void AvoidancePlayerActor::slowTime() {
    mSlowTimer->update();
    if (mSlowTimer->isTime()) {
        mSlowTimer->reset();
        mSuccessedAvoidance = false;
    }
}

bool AvoidancePlayerActor::mSuccessedAvoidance = false;
float AvoidancePlayerActor::mSlowRatio = 0.2f;
std::unique_ptr<Time> AvoidancePlayerActor::mSlowTimer = std::make_unique<Time>(0.5f);
