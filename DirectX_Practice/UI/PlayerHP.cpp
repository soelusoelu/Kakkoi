#include "PlayerHP.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Device/Renderer.h"

PlayerHP::PlayerHP(PlayerActor* player, EnemyActor* enemy) :
    mPlayer(player),
    mEnemy(enemy),
    mPreviousHp(0) {
}

PlayerHP::~PlayerHP() {
}

void PlayerHP::update() {
    if (mPlayer) {
        int hp = mPlayer->hp();
        Renderer::drawNumber(hp, Vector2::zero);
        mPreviousHp = hp;
    } else {
        Renderer::drawNumber(mPreviousHp, Vector2::zero);
    }
    Renderer::drawNumber(mEnemy->hp(), Vector2(0.f, 64.f));
}

void PlayerHP::setPlayer(PlayerActor* set) {
    mPlayer = set;
}
