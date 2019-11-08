#pragma once

#include "../Utility/Math.h"
#include <memory>

enum class ActorState {
    Active,
    Dead
};

class ComponentManagementOfActor;
class TransformComponent;

class Actor {
public:
    Actor(const char* tag = "");
    virtual ~Actor();

    //すべての更新
    void update();
    //アクター固有の更新
    virtual void updateActor() = 0;
    //描画
    virtual void drawActor() const = 0;

    //位置、角度、スケールに変更があった際に更新
    void computeWorldTransform();

    //アクター削除
    static void destroy(Actor* actor);
    static void destroy(std::shared_ptr<Actor> actor);

    //ゲッター、セッター
    std::shared_ptr<TransformComponent> getTransform() const;
    std::shared_ptr<ComponentManagementOfActor> getComponentManager() const;
    const Matrix4& getWorldTransform() const;
    ActorState getState() const;
    const char* getTag() const;

protected:
    std::shared_ptr<TransformComponent> mTransform;
    std::shared_ptr<ComponentManagementOfActor> mComponentManager;

private:
    ActorState mState;
    Matrix4 mWorldTransform;
    const char* mTag;
};

