#include "PlayerHPSP.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Renderer.h"
#include "../UI/Sprite.h"
#include "../Utility/Math.h"

PlayerHPSP::PlayerHPSP(PlayerActor* player, EnemyActor* enemy) :
    mPlayerHP(player->getComponentManager()->getComponent<HitPointComponent>()),
    mPlayerSP(player->getComponentManager()->getComponent<SPComponent>()),
    mEnemyHP(enemy->getComponentManager()->getComponent<HitPointComponent>()),
    mHpGauge(new Sprite("HP.png", Vector2(256.f, 8.f), 0.01f)),
    mSpGauge1(new Sprite("SP1.png", Vector2(256.f, 8.f), 0.03f)),
    mSpGauge2(new Sprite("SP2.png", Vector2(256.f, 8.f), 0.02f)),
    mSpGauge3(new Sprite("SP3.png", Vector2(256.f, 8.f), 0.01f)) {
    mHpGauge->setPosition(Vector2(32.f, 16.f));
    auto spPos = Vector2(32.f, mHpGauge->getScreenTextureSize().y + 24.f);
    mSpGauge1->setPosition(spPos);
    mSpGauge1->setColor(0.3f, 0.3f, 0.5f);
    mSpGauge2->setPosition(spPos + Vector2(8.f, 8.f));
    mSpGauge2->setColor(0.2f, 0.2f, 0.75f);
    mSpGauge3->setPosition(spPos + Vector2(16.f, 16.f));
    mSpGauge3->setColor(0.1f, 0.1f, 1.f);

    addSprite(mHpGauge);
    addSprite(mSpGauge1);
    addSprite(mSpGauge2);
    addSprite(mSpGauge3);
}

PlayerHPSP::~PlayerHPSP() = default;

void PlayerHPSP::update() {
    if (auto hp = mPlayerHP.lock()) {
        mHpGauge->setUV(0.f, 0.f, hp->hpRate(), 1.f);
    }

    if (auto spComp = mPlayerSP.lock()) {
        auto sp = spComp->sp();
        auto max = spComp->maxSP();
        auto one = spComp->getOneGauge();
        float rate = static_cast<float>(sp) / static_cast<float>(one);
        if (0 <= sp && sp <= one) {
            mSpGauge1->setUV(0.f, 0.f, rate, 1.f);
            mSpGauge2->setAlpha(0.f);
            mSpGauge3->setAlpha(0.f);
        } else if (one < sp && sp <= one * 2) {
            sp -= one;
            rate = static_cast<float>(sp) / static_cast<float>(one);
            mSpGauge1->setUV(0.f, 0.f, 1.f, 1.f);
            mSpGauge2->setAlpha(1.f);
            mSpGauge2->setUV(0.f, 0.f, rate, 1.f);
            mSpGauge3->setAlpha(0.f);
        } else if (one * 2 < sp) {
            sp -= one * 2;
            rate = static_cast<float>(sp) / static_cast<float>(one);
            mSpGauge1->setUV(0.f, 0.f, 1.f, 1.f);
            mSpGauge2->setAlpha(1.f);
            mSpGauge2->setUV(0.f, 0.f, 1.f, 1.f);
            mSpGauge3->setAlpha(1.f);
            mSpGauge3->setUV(0.f, 0.f, rate, 1.f);
        }
    }

    //if (auto eHP = mEnemyHP.lock()) {
    //    Renderer::drawNumber(eHP->hp(), Vector2(0.f, 64.f));
    //}
}
