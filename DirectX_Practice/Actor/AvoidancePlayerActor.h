#pragma once

#include "Actor.h"
#include "../Utility/Math.h"
#include <string>
#include <memory>

class AvoidanceComponent;
class CircleCollisionComponent;
class PlayerActor;
class SpriteComponent;
class Time;

class AvoidancePlayerActor : public Actor {
public:
    AvoidancePlayerActor(PlayerActor* player, const Vector2& position, const std::string& fileName, const Vector2& size, const Vector2& scale, const char* tag = "Avoidance");
    ~AvoidancePlayerActor();
    virtual void updateActor() override;
    virtual void drawActor() const override;
    static float slow();
    static void slowTime();

public:
    static bool mSuccessedAvoidance;
    static std::unique_ptr<Time> mSlowTimer;

private:
    AvoidanceComponent* mAvoidance;
    CircleCollisionComponent* mCircle;
    SpriteComponent* mSprite;
    static float mSlowRatio;
};
