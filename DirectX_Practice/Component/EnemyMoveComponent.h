#pragma once

#include "Component.h"
#include "../Utility/Math.h"
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
    void choiceAttack();
    void randomMove();
    void attackToPlayer();
    void circleShot();
    void hit();
    void invincible();
    void dead();

private:
    PlayerActor* mPlayer;
    Sprite* mMySprite;
    Sprite* mPlayerSprite;
    std::shared_ptr<CircleCollisionComponent> mCircle;
    std::shared_ptr<HitPointComponent> mHP;
    std::unique_ptr<Time> mInvincibleTimer;
    bool mIsInvincible;
    std::unique_ptr<Time> mNextMoveTimer;
    Vector2 mNextPos;
    bool mIsEndMove;
    bool mCompletedAttack;
};

