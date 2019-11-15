#include "EnemyMoveComponent.h"
#include "SpriteComponent.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/EnemyBullet1.h"
#include "../Actor/EnemyBullet2.h"
#include "../Actor/PlayerActor.h"
#include "../UI/Sprite.h"
#include <cassert>

EnemyMoveComponent::EnemyMoveComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mMySprite(nullptr),
    mPlayerSprite(player->getComponentManager()->getComponent<SpriteComponent>()->getSprite()),
    mEnemyBullet1(nullptr),
    mEnemyBullet2(nullptr),
    first(true),
    mHp(100) {
}

EnemyMoveComponent::~EnemyMoveComponent() = default;

void EnemyMoveComponent::start() {
    mMySprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mMySprite->setScale(0.25f);
}

void EnemyMoveComponent::update() {
    attackToPlayer();
    circleShot();
}

void EnemyMoveComponent::attackToPlayer() {
    if (mEnemyBullet1) {
        return;
    }
    mEnemyBullet1 = new EnemyBullet1(mPlayerSprite);
}

void EnemyMoveComponent::circleShot() {
    static int time = 0;
    time++;
    if (time > 180) {
        first = true;
        time = 0;
    }

    if (!first) {
        return;
    }
    first = false;

    constexpr int shotCount = 8;
    constexpr int rot = 360 / shotCount;
    for (int i = 0; i < shotCount; i++) {
        //mEnemyBullet2 = new EnemyBullet2(mPlayerSprite, i * rot);
        new EnemyBullet2(mPlayerSprite, i * rot);
    }
}
