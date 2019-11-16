#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class EnemyBullet2Component;
class Sprite;
class SpriteComponent;

class EnemyBullet2 : public Actor {
public:
    EnemyBullet2(Sprite* playerSprite, float rotation, const char* tag = "EnemyBullet");
    ~EnemyBullet2();
    virtual void updateActor() override;
    virtual void drawActor() const override;
    virtual void takeDamage(Actor* other) override;
    virtual void attack(int* hp) override;

private:
    CircleCollisionComponent* mCircle;
    EnemyBullet2Component* mEnemyBullet;
    SpriteComponent* mSprite;
    int mDamagePoint;
};