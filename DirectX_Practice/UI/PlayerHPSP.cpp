#include "PlayerHPSP.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Renderer.h"

PlayerHPSP::PlayerHPSP(PlayerActor* player, EnemyActor* enemy) :
    mPlayerHP(player->getComponentManager()->getComponent<HitPointComponent>()),
    mPlayerSP(player->getComponentManager()->getComponent<SPComponent>()),
    mEnemyHP(enemy->getComponentManager()->getComponent<HitPointComponent>()),
    mPreviousHP(0) {
}

PlayerHPSP::~PlayerHPSP() {
}

void PlayerHPSP::update() {
    if (auto pHP = mPlayerHP.lock()) {
        int hp = pHP->hp();
        Renderer::drawNumber(hp, Vector2::zero);
        mPreviousHP = hp;
    } else {
        Renderer::drawNumber(mPreviousHP, Vector2::zero);
    }

    if (auto pSP = mPlayerSP.lock()) {
        int sp = pSP->sp();
        Renderer::drawNumber(sp, Vector2(0.f, 64.f * 3));
        mPreviousSP = sp;
    } else {
        Renderer::drawNumber(mPreviousSP, Vector2(0.f, 64.f * 2));
    }

    if (auto eHP = mEnemyHP.lock()) {
        Renderer::drawNumber(eHP->hp(), Vector2(0.f, 64.f));
    }
}
