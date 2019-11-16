#pragma once

#include "Component.h"
#include <memory>

class Actor;

class HitPointComponent : public Component {
public:
    HitPointComponent(Actor* onwer, int hp);
    ~HitPointComponent();
    virtual void start() override;
    virtual void update() override;
    void takeDamage(int damage);
    void takeHeal(int heal);
    int hp() const;

private:
    int mHP;
    const int DEFAULT_HP;
};

