#include "SpecialAttack.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/SpecialAttackComponent.h"
#include "../Component/SpriteComponent.h"

SpecialAttack::SpecialAttack(PlayerActor* player, int damage, const char * tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, damage)),
    mSpecialAttack(new SpecialAttackComponent(this, player)),
    mSprite(new SpriteComponent(this, "sowrdEffect.png", Vector2(192.f, 192.f), 0.25f)) {
}

SpecialAttack::~SpecialAttack() = default;

void SpecialAttack::updateActor() {
}

void SpecialAttack::drawActor() const {
}
