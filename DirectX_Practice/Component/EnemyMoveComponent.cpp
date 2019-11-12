#include "EnemyMoveComponent.h"
#include "SpriteComponent.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/EnemyBullet1.h"
#include "../Actor/PlayerActor.h"
#include "../UI/Sprite.h"
#include <cassert>

EnemyMoveComponent::EnemyMoveComponent(Actor* onwer, PlayerActor* player) :
    Component(onwer),
    mMySprite(nullptr),
    mPlayerSprite(player->getComponentManager()->getComponent<SpriteComponent>()->getSprite()),
    mEnemyBullet1(nullptr) {
}

EnemyMoveComponent::~EnemyMoveComponent() = default;

void EnemyMoveComponent::start() {
    mMySprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mMySprite->setScale(0.5f);
}

void EnemyMoveComponent::update() {
    attackToPlayer();
}

void EnemyMoveComponent::attackToPlayer() {
    if (mEnemyBullet1) {
        return;
    }
    mEnemyBullet1 = new EnemyBullet1(mPlayerSprite);
}
