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
    Sprite* mSprite;
    Sprite* mPlayerSprite;
    bool mFirst;
    Vector2 mE2P;
    const float BULLET_SPEED;
};

