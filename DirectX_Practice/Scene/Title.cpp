#include "Title.h"
#include "../UI/Sprite.h"
#include "../UI/SpriteManager.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

Title::Title() :
    SceneBase(),
    mSprite(new Sprite("kiparupa_anm.png", Vector2(256.f, 256.f), 0.f)) {
    //new Sprite("press_space.png", Vector2(768.f, 128.f), 0.f);
    //mSprite->setUV(0.f, 0.f, 0.25f, 0.25f);
    mSprite->setUV(0.25f, 0.f, 0.5f, 0.25f);
    //mSprite->setUV(0.5f, 0.5f, 0.75f, 0.75f);
    //mSprite->setScale(0.5f);
}

Title::~Title() = default;

void Title::updateScene() {
    if (Input::getKeyDown(KeyCode::Space)) {
        next(Scene::GamePlay);
    }

    //mSprite->rotate(1.f);
}

void Title::drawScene() const {
}
