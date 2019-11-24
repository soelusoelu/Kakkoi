#include "EnemyBullet2Manager.h"
#include "EnemyBullet2.h"
#include "../Device/Time.h"

EnemyBullet2Manager::EnemyBullet2Manager(Sprite* enemySprite, bool* completedAttack, const char* tag) :
    Actor(tag),
    mCompletedAttack(completedAttack),
    mDestroyTimer(std::make_unique<Time>(2.f)) {
    constexpr int shotCount = 8;
    constexpr int rot = 360 / shotCount;
    for (int i = 0; i < shotCount; i++) {
        new EnemyBullet2(enemySprite, i * rot);
    }
}

EnemyBullet2Manager::~EnemyBullet2Manager() {
    *mCompletedAttack = true;
}

void EnemyBullet2Manager::updateActor() {
    mDestroyTimer->update();
    if (mDestroyTimer->isTime()) {
        Actor::destroy(this);
    }
}

void EnemyBullet2Manager::drawActor() const {
}
