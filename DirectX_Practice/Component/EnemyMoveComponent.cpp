#include "EnemyMoveComponent.h"
#include "SpriteComponent.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/EnemyBullet1.h"
#include "../Actor/EnemyBullet2.h"
#include "../Actor/PlayerActor.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Time.h"
#include "../System/Game.h"
#include "../UI/Sprite.h"

EnemyMoveComponent::EnemyMoveComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mPlayer(player),
    mMySprite(nullptr),
    mPlayerSprite(player->getComponentManager()->getComponent<SpriteComponent>()->getSprite()),
    mATPTimer(std::make_unique<Time>(4.f)),
    mCircleTimer(std::make_unique<Time>(3.f)),
    mInvincibleTimer(std::make_unique<Time>(0.2f)),
    mIsInvincible(false) {
}

EnemyMoveComponent::~EnemyMoveComponent() = default;

void EnemyMoveComponent::start() {
    mMySprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mMySprite->setScale(0.05f);
    mMySprite->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f, Game::WINDOW_HEIGHT / 1.5f));

    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
    mHP = mOwner->getComponentManager()->getComponent<HitPointComponent>();
}

void EnemyMoveComponent::update() {
    attackToPlayer();
    circleShot();
    hit();
}

void EnemyMoveComponent::attackToPlayer() {
    mATPTimer->update();
    if (mATPTimer->isTime()) {
        mATPTimer->reset();
        new EnemyBullet1(mPlayerSprite);
    }
}

void EnemyMoveComponent::circleShot() {
    mCircleTimer->update();
    if (mCircleTimer->isTime()) {
        mCircleTimer->reset();

        constexpr int shotCount = 8;
        constexpr int rot = 360 / shotCount;
        for (int i = 0; i < shotCount; i++) {
            new EnemyBullet2(mPlayerSprite, i * rot);
        }
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

        auto spComp = mPlayer->getComponentManager()->getComponent<SPComponent>();
        spComp->heal(5);
        auto sp = spComp->sp();
        if (100 < sp && sp <= 105) {
            spComp->set(100);
        } else if (200 < sp && sp <= 205) {
            spComp->set(200);
        }
    }
}

void EnemyMoveComponent::invincible() {
    mInvincibleTimer->update();
    if (mInvincibleTimer->isTime()) {
        mInvincibleTimer->reset();
        mIsInvincible = false;
    }
}
