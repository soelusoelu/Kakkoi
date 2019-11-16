#pragma once

#include "Component.h"

class Actor;

class PlayerAttackComponent : public Component {
public:
    PlayerAttackComponent(Actor* onwer);
    ~PlayerAttackComponent();
    virtual void update() override;

private:
    int mCurrentTime;
    int DESTROY_TIME;
};

