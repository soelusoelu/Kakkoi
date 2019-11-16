#pragma once

#include "Component.h"

class Actor;
class Sprite;

enum class PlayerState {
    OnGround,
    JumpNow
};

enum class Direction {
    Right,
    Left
};

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
    void posClamp();
    void canAttack();
    void attack();

private:
    Sprite* mSprite;
    const float MOVE_SPEED;
    const float FALL_SPEED;
    float mCurrentJumpPower;
    float mX; //ジャンプ二次関数用
    int mCurrentAttackTime;
    const int NEXT_ATTACK_TIME;
    bool mCanAttack;
    PlayerState mState;
    Direction mDir;
};
