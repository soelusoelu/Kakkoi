#pragma once

#include "Component.h"

class Actor;

class SPComponent : public Component {
public:
    SPComponent(Actor* onwer, int sp);
    ~SPComponent();
    virtual void update() override;
    void set(int sp);
    bool use(int sp);
    void takeHeal(int sp);
    int sp() const;

private:
    int mSP;
    int MAX_SP;
};

