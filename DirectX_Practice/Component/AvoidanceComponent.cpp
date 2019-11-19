#include "AvoidanceComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Device/Time.h"

AvoidanceComponent::AvoidanceComponent(Actor* onwer) :
    Component(onwer),
    mCircle(nullptr),
    mDestroyTimer(std::make_unique<Time>(0.25f)) {
}

AvoidanceComponent::~AvoidanceComponent() = default;

void AvoidanceComponent::start() {
    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
}

void AvoidanceComponent::update() {
    auto col = mCircle->onCollisionEnter();
    //auto col = mCircle->onCollisionStay();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() == "EnemyBullet") {
            AvoidancePlayerActor::mSuccessedAvoidance = true;
            AvoidancePlayerActor::mSlowTimer->reset();
        }
    }

    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(mOwner);
    }
}
