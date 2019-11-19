#pragma once

#include "Component.h"
#include <memory>

class Actor;
class CircleCollisionComponent;
class EnemyBullet1;
class EnemyBullet2;
class HitPointComponent;
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
    void hit();
    void invincible();

private:
    PlayerActor* mPlayer;
    Sprite* mMySprite;
    Sprite* mPlayerSprite;
    std::shared_ptr<CircleCollisionComponent> mCircle;
    std::shared_ptr<HitPointComponent> mHP;
    std::unique_ptr<Time> mATPTimer;
    std::unique_ptr<Time> mCircleTimer;
    std::unique_ptr<Time> mInvincibleTimer;
    bool mIsInvincible;
};

