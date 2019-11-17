#pragma once

#include "Component.h"
#include <memory>

class Actor;
class EnemyBullet1;
class EnemyBullet2;
class PlayerActor;
class Sprite;
class Time;

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

private:
    void attackToPlayer();
    void circleShot();

private:
    Sprite* mMySprite;
    Sprite* mPlayerSprite;
    std::unique_ptr<Time> mATPTimer;
    std::unique_ptr<Time> mCircleTimer;
};

