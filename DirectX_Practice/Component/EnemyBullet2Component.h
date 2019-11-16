#pragma once

#include "Component.h"
#include "../Utility/Math.h"

class Actor;
class Sprite;

class EnemyBullet2Component : public Component {
public:
    EnemyBullet2Component(Actor* owner, Sprite* playerSprite, float rotation);
    ~EnemyBullet2Component();
    virtual void start() override;
    virtual void update() override;

private:
    void destroy();

private:
    Sprite* mSprite;
    Sprite* mPlayerSprite;
    Vector2 mVelocity;
    float ROTATION;
    float BULLET_SPEED;
};

