#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <string>
#include <memory>

class CircleCollisionComponent;
class SpriteComponent;
class Time;

class AvoidancePlayerActor : public Actor {
public:
    AvoidancePlayerActor(const Vector2& position, const std::string& fileName, const Vector2& size, const Vector2& scale, const char* tag = "Avoidance");
    ~AvoidancePlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;

private:
    CircleCollisionComponent* mCircle;
    SpriteComponent* mSprite;
    std::unique_ptr<Time> mDestroyTimer;
};
