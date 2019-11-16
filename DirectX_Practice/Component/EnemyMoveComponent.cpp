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
    mPlayerSprite(player->getComponentManager()->getComponent<SpriteComponent>()->getSprite()) {
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
    static int time = 0;
    time++;
    if (time > 240) {
        time = 0;
    } else {
        return;
    }

    new EnemyBullet1(mPlayerSprite);
}

void EnemyMoveComponent::circleShot() {
    static int time = 0;
    time++;
    if (time > 180) {
        time = 0;
    } else {
        return;
    }

    constexpr int shotCount = 8;
    constexpr int rot = 360 / shotCount;
    for (int i = 0; i < shotCount; i++) {
        new EnemyBullet2(mPlayerSprite, i * rot);
    }
}
