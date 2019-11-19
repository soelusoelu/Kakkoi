#include "AvoidanceComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Time.h"

AvoidanceComponent::AvoidanceComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mCircle(nullptr),
    mDestroyTimer(std::make_unique<Time>(0.25f)),
    mPlayer(player) {
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

            auto spComp = mPlayer->getComponentManager()->getComponent<SPComponent>();
            auto sp = spComp->sp();
            int currentMaxSP = 0;
            if (sp < 100) {
                currentMaxSP = 100;
            } else if (100 <= sp && sp < 200) {
                currentMaxSP = 200;
            } else if (200 <= sp && sp < 300) {
                currentMaxSP = 300;
            }
            spComp->heal(15);
            if (spComp->sp() > currentMaxSP) {
                spComp->set(currentMaxSP);
            }
        }
    }

    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(mOwner);
    }
}
