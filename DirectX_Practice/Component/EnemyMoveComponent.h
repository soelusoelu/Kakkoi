#pragma once

#include "Component.h"
#include <memory>

class Actor;
class PlayerActor;
class Sprite;
class EnemyBullet1;

class EnemyMoveComponent : public Component {
public:
    EnemyMoveComponent(Actor* onwer, PlayerActor* player);
    ~EnemyMoveComponent();
    virtual void start() override;
    virtual void update() override;
    void attackToPlayer();

private:
    Sprite* mMySprite;
    Sprite* mPlayerSprite;

    EnemyBullet1* mEnemyBullet1;
};

