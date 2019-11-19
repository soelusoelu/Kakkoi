#include "PlayerAttack.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/PlayerAttackComponent.h"
#include "../Component/SpriteComponent.h"
#include "../UI/Sprite.h"

PlayerAttack::PlayerAttack(const Vector2& pos, int damage, const char* tag) :
    Actor(tag),
    mCircle(new CircleCollisionComponent(this)),
    mDamage(new DamageComponent(this, damage)),
    mAttack(new PlayerAttackComponent(this)),
    mSprite(new SpriteComponent(this, "sowrdEffect.png", Vector2(192.f, 192.f), 0.3f)) {
    auto sprite = mSprite->getSprite();
    sprite->setScale(0.5f);
    sprite->setPosition(pos);
}

PlayerAttack::~PlayerAttack() = default;

void PlayerAttack::updateActor() {
}

void PlayerAttack::drawActor() const {
}
