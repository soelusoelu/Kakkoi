#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class EnemyBullet1Component;
class Sprite;
class SpriteComponent;

class EnemyBullet1 : public Actor {
public:
    EnemyBullet1(Sprite* playerSprite, const char* tag = "EnemyBullet");
    ~EnemyBullet1();
    virtual void updateActor() override;
    virtual void drawActor() const override;
    virtual void takeDamage(Actor* other) override;
    virtual void attack(int* hp) override;

private:
    CircleCollisionComponent* mCircle;
    EnemyBullet1Component* mEnemyBullet;
    SpriteComponent* mSprite;
    int mDamagePoint;
};