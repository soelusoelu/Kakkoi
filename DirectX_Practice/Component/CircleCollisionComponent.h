#pragma once

#include "Component.h"
#include "../Utility/Collision.h"
#include "../Utility/Math.h"
#include <memory>

class Actor;
class Sprite;

class CircleCollisionComponent : public Component {
public:
    CircleCollisionComponent(Actor* onwer);
    ~CircleCollisionComponent();
    virtual void start() override;
    virtual void update() override;

private:
    std::shared_ptr<Circle> mCircle;
    //Circle mCircle;
    Sprite* mSprite;
};

