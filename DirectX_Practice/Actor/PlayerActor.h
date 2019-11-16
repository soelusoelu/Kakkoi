#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class HitPointComponent;
class PlayerMoveComponent;
class SpriteComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    HitPointComponent* mHP;
    PlayerMoveComponent* mPlayerMove;
    SpriteComponent* mSprite;
};

