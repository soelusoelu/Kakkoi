#pragma once

#include "Component.h"
#include <memory>

class Actor;
class PlayerActor;
class Sprite;
class EnemyBullet1;
class EnemyBullet2;

enum class BossHpState {
    Max_HP,
    Harf_HP
};

class EnemyMoveComponent : public Component {
public:
    EnemyMoveComponent(Actor* onwer, PlayerActor* player);
    ~EnemyMoveComponent();
    virtual void start() override;
    virtual void update() override;
    void attackToPlayer();
    void circleShot();

private:
    Sprite* mMySprite;
    Sprite* mPlayerSprite;
};

