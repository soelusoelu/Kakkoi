#pragma once

#include "Component.h"

class Actor;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, int updateOrder = 10);
    virtual void update() override;

private:
    float mSpeed;
};
