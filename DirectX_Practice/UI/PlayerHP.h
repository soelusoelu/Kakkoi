#pragma once

#include "UI.h"

class PlayerActor;

class PlayerHP : public UI {
public:
    PlayerHP(PlayerActor* player);
    ~PlayerHP();
    virtual void update() override;
    void setPlayer(PlayerActor* set);

private:
    PlayerActor* mPlayer;
    int mPreviousHp;
};
