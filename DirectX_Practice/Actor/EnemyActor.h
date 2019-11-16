#pragma once

#include "Actor.h"

class CircleCollisionComponent;
class EnemyMoveComponent;
class SpriteComponent;
class PlayerActor;

class EnemyActor : public Actor {
public:
    EnemyActor(PlayerActor* player, const char* tag = "Enemy");
    ~EnemyActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;
    virtual void attack(int* hp) override;
    const int hp() const;

private:
    CircleCollisionComponent* mCircle;
    EnemyMoveComponent* mEnemyMove;
    SpriteComponent* mSprite;
    int mHp;
};

