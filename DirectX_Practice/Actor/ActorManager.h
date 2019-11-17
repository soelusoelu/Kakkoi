#pragma once

#include "../Utility/IManager.h"
#include "../Utility/Singleton.h"
#include <memory>
#include <list>

class Actor;
class PlayerActor;

class ActorManager : public IManager<Actor> {
public:
    ActorManager();
    ~ActorManager();
    virtual void update() override;
    virtual void draw() const override;
    static void add(Actor* add);
    virtual void remove() override;
    virtual void clear() override;

    //アクター配列の中からプレイヤーを取得
    std::shared_ptr<PlayerActor> getPlayer() const;

private:
    ActorManager(const ActorManager&) = delete;
    ActorManager& operator=(const ActorManager&) = delete;

private:
    static std::list<std::shared_ptr<Actor>> mActors;
    static std::list<std::shared_ptr<Actor>> mPendingActors;
    static bool mUpdatingActors;
};

