#include "EnemyMoveComponent.h"
#include "SpriteComponent.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/EnemyBullet1Manager.h"
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
    mNextMoveTimer(std::make_unique<Time>(3.f)),
    mNextPos(Vector2::zero),
    mIsEndMove(false),
    mCompletedAttack(true),
    mDir(Direction::Left),
    mMoveSpeed(0.01f),
    DANGEROUS_RATE(0.5f),
    DYING_RATE(0.25f) {
}

EnemyMoveComponent::~EnemyMoveComponent() = default;

void EnemyMoveComponent::start() {
    mMySprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mMySprite->setScale(0.5f, true);
    mMySprite->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f - mMySprite->getScreenTextureSize().x, Game::WINDOW_HEIGHT / 2.f - mMySprite->getScreenTextureSize().y));
    mMySprite->setUV(0.f, 0.f, 0.5f, 0.5f);

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

    if (mHP->hpRate() < DYING_RATE) {
        if (Random::randomRange(0, 100) < 30) {
            attackToPlayer(3);
        } else {
            circleShot(12);
        }
    } else {
        if (Random::randomRange(0, 100) < 30) {
            attackToPlayer(1);
        } else {
            circleShot(8);
        }
    }

    if (mDir == Direction::Left) {
        mMySprite->setUV(0.5f, 0.f, 1.f, 0.5f);
    } else {
        mMySprite->setUV(0.5f, 0.5f, 1.f, 1.f);
    }
}

void EnemyMoveComponent::randomMove() {
    if (mCompletedAttack) {
        mNextPos = Vector2(
            Random::randomRange(0.f, Game::WINDOW_WIDTH - mMySprite->getScreenTextureSize().x),
            Random::randomRange(Game::WINDOW_HEIGHT / 2.f - mMySprite->getScreenTextureSize().y, Game::WINDOW_HEIGHT - mMySprite->getScreenTextureSize().y)
        );
        mCompletedAttack = false;
        mIsEndMove = false;
    }
    mMySprite->setPosition(Vector2::lerp(mMySprite->getPosition(), mNextPos, mMoveSpeed));

    auto dir = mPlayerSprite->getPosition().x - mMySprite->getPosition().x;
    mDir = dir < 0 ? Direction::Left : Direction::Right;

    if (!mIsEndMove) {
        if (mDir == Direction::Left) {
            mMySprite->setUV(0.f, 0.f, 0.5f, 0.5f);
        } else {
            mMySprite->setUV(0.f, 0.5f, 0.5f, 1.f);
        }
    }

    if (Vector2::distance(mMySprite->getPosition(), mNextPos) < 3.f) {
        mIsEndMove = true;
    }
}

void EnemyMoveComponent::attackToPlayer(int shotCount) {
    new EnemyBullet1Manager(mMySprite, mPlayerSprite, &mCompletedAttack, shotCount, mHP->hpRate());
}

void EnemyMoveComponent::circleShot(int shotCount) {
    new EnemyBullet2Manager(mMySprite, &mCompletedAttack, shotCount, mHP->hpRate());
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

        if (mHP->hpRate() < DANGEROUS_RATE && mHP->hpRate() >= DYING_RATE) {
            //mMySprite->setColor(1.f, 1.f, 0.f);
            mNextMoveTimer->setLimitTime(2.5f);
            mMoveSpeed = 0.05f;
        }
        if (mHP->hpRate() < DYING_RATE) {
            //mMySprite->setColor(1.f, 0.f, 0.f);
            //mNextMoveTimer->setLimitTime(2.f);
            mMoveSpeed = 0.1f;
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

void EnemyMoveComponent::dead() {
    if (mHP->hp() <= 0) {
        Actor::destroy(mOwner);
    }
}
