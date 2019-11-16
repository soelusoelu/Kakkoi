#include "PlayerHP.h"
#include "../Actor/PlayerActor.h"
#include "../Device/Renderer.h"

PlayerHP::PlayerHP(PlayerActor* player) :
    mPlayer(player),
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
}

void PlayerHP::setPlayer(PlayerActor* set) {
    mPlayer = set;
}
