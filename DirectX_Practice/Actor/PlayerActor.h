#pragma once

#include "Actor.h"

class PlayerMoveComponent;

class PlayerActor : public Actor {
public:
    PlayerActor(const char* tag = "Player");
    ~PlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    PlayerMoveComponent* mPlayerMove;
};

