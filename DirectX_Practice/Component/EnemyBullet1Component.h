#pragma once

#include "Component.h"
#include "../Utility/Math.h"

class Actor;
class Sprite;

class EnemyBullet1Component : public Component {
public:
    EnemyBullet1Component(Actor* onwer, Sprite* playerSprite);
    ~EnemyBullet1Component();
    virtual void start() override;
    virtual void update() override;

private:
    void move();
    void destroy();

private:
    Sprite* mSprite;
    Sprite* mPlayerSprite;
    Vector2 mE2P;
    const float BULLET_SPEED;
    const float MAX_SCALE;
    const float MIN_SCALE;
    const float ROTATE_SPEED;
    const float SCALING_SPEED;
};

