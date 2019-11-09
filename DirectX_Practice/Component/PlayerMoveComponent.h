#pragma once

#include "Component.h"

class Actor;
class Sprite;

class PlayerMoveComponent : public Component {
public:
    PlayerMoveComponent(Actor* owner, int updateOrder = 10);
    virtual void start() override;
    virtual void update() override;

private:
    Sprite* mSprite;
    float mSpeed;
};
