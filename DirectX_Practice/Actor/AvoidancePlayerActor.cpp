#include "AvoidancePlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"
#include "../UI/Sprite.h"

AvoidancePlayerActor::AvoidancePlayerActor(const Vector2& position, const std::string& fileName, const Vector2& size, const Vector2& scale, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mSprite(new SpriteComponent(this, fileName, size, 0.51f)),
    mDestroyTimer(std::make_unique<Time>(0.25f)) {
    auto s = mSprite->getSprite();
    //s->setAlpha(0.5f);
    s->setScale(scale, true);
    s->setPosition(position);
}

AvoidancePlayerActor::~AvoidancePlayerActor() = default;

void AvoidancePlayerActor::updateActor() {
    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() == "EnemyBullet") {
            break;
        }
    }

    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(this);
    }
}

void AvoidancePlayerActor::drawActor() const {
}
