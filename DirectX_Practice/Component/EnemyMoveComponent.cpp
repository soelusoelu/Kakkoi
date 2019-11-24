#include "EnemyMoveComponent.h"
#include "SpriteComponent.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/EnemyBullet1.h"
#include "../Actor/EnemyBullet2Manager.h"
#include "../Actor/PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Random.h"
#include "../Device/Time.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"

EnemyMoveComponent::EnemyMoveComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mPlayer(player),
    mMySprite(nullptr),
    mPlayerSprite(player->getComponentManager()->getComponent<SpriteComponent>()->getSprite()),
    mInvincibleTimer(std::make_unique<Time>(0.2f)),
    mIsInvincible(false),
    mNextMoveTimer(std::make_unique<Time>(5.f)),
    mNextPos(Vector2::zero),
    mIsEndMove(false),
    mCompletedAttack(true) {
}

EnemyMoveComponent::~EnemyMoveComponent() = default;

void EnemyMoveComponent::start() {
    mMySprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mMySprite->setScale(0.5f, true);
    mMySprite->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f - mMySprite->getScreenTextureSize().x, Game::WINDOW_HEIGHT / 2.f + -mMySprite->getScreenTextureSize().y));

    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
    mHP = mOwner->getComponentManager()->getComponent<HitPointComponent>();
}

void EnemyMoveComponent::update() {
    choiceAttack();
    hit();
    dead();
}

void EnemyMoveComponent::choiceAttack() {
    randomMove();

    mNextMoveTimer->update();
    if (!mNextMoveTimer->isTime()) {
        return;
    }
    mNextMoveTimer->reset();

    if (!mIsEndMove) {
        return;
    }
    if (Random::randomRange(0, 100) < 30) {
        attackToPlayer();
    } else {
        circleShot();
    }
}

void EnemyMoveComponent::randomMove() {
    if (mCompletedAttack) {
        mNextPos = Vector2(
            Random::randomRange(0.f, Game::WINDOW_WIDTH - mMySprite->getScreenTextureSize().x),
            Random::randomRange(Game::WINDOW_HEIGHT / 2.f, Game::WINDOW_HEIGHT - mMySprite->getScreenTextureSize().y)
        );
        mCompletedAttack = false;
    }
    mMySprite->setPosition(Vector2::lerp(mMySprite->getPosition(), mNextPos, 0.016f));
    auto dis = Vector2::distance(mMySprite->getPosition(), mNextPos);
    if (Vector2::distance(mMySprite->getPosition(), mNextPos) < 4.f) {
        mIsEndMove = true;
    }
}

void EnemyMoveComponent::attackToPlayer() {
    new EnemyBullet1(mMySprite, mPlayerSprite, &mCompletedAttack);
}

void EnemyMoveComponent::circleShot() {
    constexpr int shotCount = 8;
    constexpr int rot = 360 / shotCount;
    for (int i = 0; i < shotCount; i++) {
        new EnemyBullet2Manager(mMySprite, &mCompletedAttack);
    }
}

void EnemyMoveComponent::hit() {
    if (mIsInvincible) {
        invincible();
        return;
    }

    auto col = mCircle->onCollisionStay();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "PlayerAttack") {
            return;
        }

        mIsInvincible = true;

        auto damage = c->getOwner()->getComponentManager()->getComponent<DamageComponent>();
        mHP->takeDamage(damage->damage());
    }
}

void EnemyMoveComponent::invincible() {
    mInvincibleTimer->update();
    if (mInvincibleTimer->isTime()) {
        mInvincibleTimer->reset();
        mIsInvincible = false;
    }
}

void EnemyMoveComponent::dead() {
    if (mHP->hp() <= 0) {
        Actor::destroy(mOwner, 0.1f);
    }
}
