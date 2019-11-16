#pragma once

#include "UI.h"

class PlayerActor;
class EnemyActor;

class PlayerHP : public UI {
public:
    PlayerHP(PlayerActor* player, EnemyActor* enemy);
    ~PlayerHP();
    virtual void update() override;
    void setPlayer(PlayerActor* set);

private:
    PlayerActor* mPlayer;
    EnemyActor* mEnemy;
    int mPreviousHp;
};
