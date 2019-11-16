#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class PlayerMoveComponent;
class SpriteComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;
    virtual void takeDamage(Actor* other) override;
    virtual void attack(int* hp) override;
    const int hp() const;

private:
    CircleCollisionComponent* mCircle;
    PlayerMoveComponent* mPlayerMove;
    SpriteComponent* mSprite;
    int mHp;
};

