#pragma once

#include "UI.h"
#include <memory>

class PlayerActor;
class EnemyActor;
class HitPointComponent;

class PlayerHP : public UI {
public:
    PlayerHP(PlayerActor* player, EnemyActor* enemy);
    ~PlayerHP();
    virtual void update() override;

private:
    std::weak_ptr<HitPointComponent> mPlayerHP;
    std::weak_ptr<HitPointComponent> mEnemyHP;
    int mPreviousHp;
};
