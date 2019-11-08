#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Component/TransformComponent.h"
#include "../Device/Physics.h"
#include "../Device/Renderer.h"
#include "../UI/Pause.h"
#include "../UI/SpriteManager.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"

GamePlay::GamePlay() :
    SceneBase(),
    mActorManager(std::make_shared<ActorManager>()),
    mState(GameState::Play) {
    new PlayerActor();
}

GamePlay::~GamePlay() {
    mActorManager->clear();
    Renderer::clear();
}

void GamePlay::updateScene() {
    if (mState == GameState::Play) {
        mActorManager->update();

        //総当たり判定
        Singleton<Physics>::instance().sweepAndPrune();

        if (Input::getKeyDown(KeyCode::Escape)) {
            mUIManager->add(new Pause(shared_from_this()));
        }
    }
}

void GamePlay::drawScene() const {
    mActorManager->draw();
    Singleton<Camera>::instance().update(mActorManager->getPlayer());
}

GameState GamePlay::getState() const {
    return mState;
}

void GamePlay::setState(GameState state) {
    mState = state;
}
