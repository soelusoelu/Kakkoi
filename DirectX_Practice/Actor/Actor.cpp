#include "Actor.h"
#include "ActorManager.h"
#include "ComponentManagementOfActor.h"
#include "../Component/TransformComponent.h"

Actor::Actor(const char* tag) :
    mTransform(std::make_shared<TransformComponent>()),
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
    if (mTransform->getRecomputeTransform()) {
        mTransform->setRecomputeTransform(false);

        mWorldTransform = Matrix4::createScale(mTransform->getScale());
        mWorldTransform *= Matrix4::createFromQuaternion(mTransform->getRotation());
        mWorldTransform *= Matrix4::createTranslation(mTransform->getPosition());

        mComponentManager->executeOnUpdateWorldTransform();
    }
}

void Actor::destroy(Actor* actor) {
    actor->mState = ActorState::Dead;
}

void Actor::destroy(std::shared_ptr<Actor> actor) {
    actor->mState = ActorState::Dead;
}

std::shared_ptr<TransformComponent> Actor::getTransform() const {
    return mTransform;
}

std::shared_ptr<ComponentManagementOfActor> Actor::getComponentManager() const {
    return mComponentManager;
}

const Matrix4& Actor::getWorldTransform() const {
    return mWorldTransform;
}

ActorState Actor::getState() const {
    return mState;
}

const char* Actor::getTag() const {
    return mTag;
}
