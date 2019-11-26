#include "Title.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

Title::Title() :
    SceneBase(),
    mSprite(new Sprite("Title.png", Vector2(1080.f, 720.f), 0.1f)) {
}

Title::~Title() = default;

void Title::updateScene() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::GamePlay);
    }
}

void Title::drawScene() const {
}
