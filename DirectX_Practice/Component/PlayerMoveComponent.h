#pragma once

#include "Component.h"
#include <memory>

enum class PlayerState {
    OnGround,
    Jump
};

enum class Direction {
    Right,
    Left
};

class Actor;
class CircleCollisionComponent;
class HitPointComponent;
class Sprite;
class Time;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, int updateOrder = 10);
    ~PlayerMoveComponent();
    virtual void start() override;
    virtual void update() override;

private:
    void move();
    void jump();
    void jumpUpdate();
    void fall();
    void avoidance();
    void posClamp();
    void canAttack();
    void attack();
    void hit();

private:
    Sprite* mSprite;
    std::shared_ptr<CircleCollisionComponent> mCircle;
    std::shared_ptr<HitPointComponent> mHP;
    const float MOVE_SPEED;
    const float FALL_SPEED;
    float mCurrentJumpPower;
    float mX; //ジャンプ二次関数用
    const int AVOIDANCE_LENGTH;
    std::unique_ptr<Time> mAttackTimer;
    bool mCanAttack;
    PlayerState mState;
    Direction mDir;
};
