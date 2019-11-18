#pragma once

#include "Component.h"
#include <memory>

class Actor;
class Time;

class PlayerAttackComponent : public Component {
public:
    PlayerAttackComponent(Actor* onwer);
    ~PlayerAttackComponent();
    virtual void update() override;

private:
    std::unique_ptr<Time> mTimer;
};

