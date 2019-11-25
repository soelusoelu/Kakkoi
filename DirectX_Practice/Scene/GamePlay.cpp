#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Device/Physics.h"
#include "../Device/Renderer.h"
#include "../Device/Sound.h"
#include "../UI/Pause.h"
#include "../UI/PlayerHPSP.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

GamePlay::GamePlay() :
    SceneBase(),
    mActorManager(std::make_shared<ActorManager>()),
    mState(GameState::Play) {
    auto p = new PlayerActor();
    auto e = new EnemyActor(p);
    mUIManager->add(new PlayerHPSP(p, e));
    new Sprite("bossroom.png", Vector2(1080.f, 720.f), 0.99f);
}

GamePlay::~GamePlay() {
    mActorManager->clear();
    Renderer::clear();
    Physics::clear();
}

void GamePlay::updateScene() {
    if (mState == GameState::Play) {
        mActorManager->update();
        AvoidancePlayerActor::slowTime();

        Physics::sweepAndPrune();

        if (Input::getKeyDown(KeyCode::Escape)) {
            mUIManager->add(new Pause(shared_from_this()));
        }
        if (!mActorManager->getActor<EnemyActor>() || !mActorManager->getPlayer()) {
            next(Scene::Title);
        }
    }
}

void GamePlay::drawScene() const {
    mActorManager->draw();
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
