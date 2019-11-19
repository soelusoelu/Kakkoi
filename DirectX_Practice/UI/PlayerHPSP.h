#pragma once

#include "UI.h"
#include <memory>

class PlayerActor;
class EnemyActor;
class HitPointComponent;
class SPComponent;

class PlayerHPSP : public UI {
public:
    PlayerHPSP(PlayerActor* player, EnemyActor* enemy);
    ~PlayerHPSP();
    virtual void update() override;

private:
    std::weak_ptr<HitPointComponent> mPlayerHP;
    std::weak_ptr<SPComponent> mPlayerSP;
    std::weak_ptr<HitPointComponent> mEnemyHP;
    int mPreviousHP;
    int mPreviousSP;
};