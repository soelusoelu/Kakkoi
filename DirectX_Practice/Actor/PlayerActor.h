#pragma once

#include "Actor.h"

class PlayerMoveComponent;
class SpriteComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    PlayerMoveComponent* mPlayerMove;
    SpriteComponent* mSprite;
};

