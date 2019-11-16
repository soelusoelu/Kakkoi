#include "PlayerHP.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Component/HitPointComponent.h"
#include "../Device/Renderer.h"

PlayerHP::PlayerHP(PlayerActor* player, EnemyActor* enemy) :
    mPlayerHP(player->getComponentManager()->getComponent<HitPointComponent>()),
    mEnemyHP(enemy->getComponentManager()->getComponent<HitPointComponent>()),
    mPreviousHp(0) {
}

PlayerHP::~PlayerHP() {
}

void PlayerHP::update() {
    if (auto pHP = mPlayerHP.lock()) {
        int hp = pHP->hp();
        Renderer::drawNumber(hp, Vector2::zero);
        mPreviousHp = hp;
    } else {
        Renderer::drawNumber(mPreviousHp, Vector2::zero);
    }
    if (auto eHP = mEnemyHP.lock()) {
        Renderer::drawNumber(eHP->hp(), Vector2(0.f, 64.f));
    }
}
