#include "PlayerHPSP.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Renderer.h"
#include "../UI/Sprite.h"

PlayerHPSP::PlayerHPSP(PlayerActor* player, EnemyActor* enemy) :
    mPlayerHP(player->getComponentManager()->getComponent<HitPointComponent>()),
    mPlayerSP(player->getComponentManager()->getComponent<SPComponent>()),
    mEnemyHP(enemy->getComponentManager()->getComponent<HitPointComponent>()),
    mHpGauge(new Sprite("HP.png", Vector2(128.f, 32.f), 0.01f)),
    mSpGauge(new Sprite("HP.png", Vector2(128.f, 32.f), 0.01f)) {
    mHpGauge->setPosition(Vector2(32.f, 16.f));
    mHpGauge->setScale(Vector2(2.f, 1.f));
    mSpGauge->setPosition(Vector2(32.f, mHpGauge->getScreenTextureSize().y + 16.f));
    mSpGauge->setColor(0.f, 0.f, 1.f);
    addSprite(mHpGauge);
    addSprite(mSpGauge);
}

PlayerHPSP::~PlayerHPSP() = default;

void PlayerHPSP::update() {
    if (auto pHP = mPlayerHP.lock()) {
        mHpGauge->setUV(0.f, 0.f, pHP->hpRate(), 0.5f);
    }

    if (auto pSP = mPlayerSP.lock()) {
        mSpGauge->setUV(0.f, 0.f, pSP->spRate(), 0.5f);
    }

    //if (auto eHP = mEnemyHP.lock()) {
    //    Renderer::drawNumber(eHP->hp(), Vector2(0.f, 64.f));
    //}
}
