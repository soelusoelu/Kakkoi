#include "AnimationComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Component/SpriteComponent.h"
#include "../Device/Time.h"
#include "../UI/Sprite.h"

AnimationComponent::AnimationComponent(Actor* owner, float changeTimerSec, const Vector2& oneSpriteSize) :
    Component(owner),
    mChangeTimer(std::make_unique<Time>(changeTimerSec)),
    mSprite(nullptr),
    mSize(oneSpriteSize),
    mWidthCount(0),
    mHeightCount(0),
    mCurrentIndex(0),
    mVerticalIndex(0) {
}

AnimationComponent::~AnimationComponent() = default;

void AnimationComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mWidthCount = mSprite->getTextureSize().x / (mSize.x - 0.5f);
    mHeightCount = mSprite->getTextureSize().y / (mSize.y - 0.5f);
}

void AnimationComponent::update() {
    mChangeTimer->update();
    if (mChangeTimer->isTime()) {
        mChangeTimer->reset();
        change();
    }
}

void AnimationComponent::change() {
    mCurrentIndex = (mCurrentIndex + mWidthCount + 1) % mWidthCount;

    auto size = mSprite->getTextureSize();
    auto l = static_cast<float>(mCurrentIndex) / static_cast<float>(mWidthCount);
    auto t = static_cast<float>(mVerticalIndex) / static_cast<float>(mHeightCount);
    mSprite->setUV(
        l,
        t,
        l + mSize.x / mSprite->getTextureSize().x,
        t + mSize.y / mSprite->getTextureSize().y
    );
}

void AnimationComponent::set(int verticalIndex) {
    mVerticalIndex = verticalIndex;
    mChangeTimer->setOverLimit();
}
