#include "GamePlay.h"
#include "../Actor/ActorManager.h"
#include "../Actor/EnemyActor.h"
#include "../Actor/PlayerActor.h"
#include "../Camera/Camera.h"
#include "../Device/Renderer.h"
#include "../Device/Sound.h"
#include "../UI/Pause.h"
#include "../UI/SpriteManager.h"
#include "../UI/UIManager.h"
#include "../Utility/Input.h"

GamePlay::GamePlay() :
    SceneBase(),
    mActorManager(std::make_shared<ActorManager>()),
    mState(GameState::Play) {
    auto p = new PlayerActor();
    new EnemyActor(p);
}

GamePlay::~GamePlay() {
    mActorManager->clear();
    Renderer::clear();
}

void GamePlay::updateScene() {
    if (mState == GameState::Play) {
        mActorManager->update();

        if (Input::getKeyDown(KeyCode::Escape)) {
            mUIManager->add(new Pause(shared_from_this()));
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
