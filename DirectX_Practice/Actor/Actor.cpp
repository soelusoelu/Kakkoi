#include "Actor.h"
#include "ActorManager.h"
#include "ComponentManagementOfActor.h"

Actor::Actor(const char* tag) :
    mComponentManager(std::make_shared<ComponentManagementOfActor>()),
    mState(ActorState::Active),
    mTag(tag) {
    ActorManager::add(this);
}

Actor::~Actor() = default;

void Actor::update() {
    mComponentManager->start();
    if (mState == ActorState::Active) {
        computeWorldTransform();

        mComponentManager->update();
        updateActor();

        computeWorldTransform();
    }
}

void Actor::computeWorldTransform() {
    //mComponentManager->executeOnUpdateWorldTransform();
}

void Actor::destroy(Actor * actor) {
    actor->mState = ActorState::Dead;
}

void Actor::destroy(std::shared_ptr<Actor> actor) {
    actor->mState = ActorState::Dead;
}

std::shared_ptr<ComponentManagementOfActor> Actor::getComponentManager() const {
    return mComponentManager;
}

ActorState Actor::getState() const {
    return mState;
}

const char* Actor::getTag() const {
    return mTag;
}
