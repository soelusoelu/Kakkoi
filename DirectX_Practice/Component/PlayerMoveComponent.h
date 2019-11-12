#pragma once

#include "Component.h"

class Actor;
class Sprite;

enum class PlayerState {
    OnGround,
    JumpNow
};

class Sprite;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, int updateOrder = 10);
    ~PlayerMoveComponent();
    virtual void start() override;
    virtual void update() override;
    void move();
    void jump();
    void jumpUpdate();
    void fall();
    void posClamp();

private:
    Sprite* mSprite;
    const float MOVE_SPEED;
    const float FALL_SPEED;
    float mCurrentJumpPower;
    float mX; //ジャンプ二次関数用
    PlayerState mState;
};
