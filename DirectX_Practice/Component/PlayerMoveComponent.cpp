#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../UI/Sprite.h"
#include "../Component/SpriteComponent.h"
#include "../System/Game.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mSprite(nullptr),
    MOVE_SPEED(2.f),
    FALL_SPEED(1.f),
    mCurrentJumpPower(0.f),
    mX(0.f),
    mState(PlayerState::OnGround) {
}

PlayerMoveComponent::~PlayerMoveComponent() {
}

void PlayerMoveComponent::start() {
    mSprite = mOwner->getComponentManager()->getComponent<SpriteComponent>()->getSprite();
    mSprite->setScale(0.1f);
    mSprite->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f, Game::WINDOW_HEIGHT - (mSprite->getSize().y * mSprite->getScale().y)));
}

void PlayerMoveComponent::update() {
    move();
    jump();
    jumpUpdate();
    fall();
    posClamp();

    //mEffect->rotate(8.f);
    //static bool is = true;
    //if (is) {
    //    mEffect->setScale(mEffect->getScale().x - 0.01f, true);
    //    if (mEffect->getScale().x <= 0.2f) {
    //        is = false;
    //    }
    //} else {
    //    mEffect->setScale(mEffect->getScale().x + 0.03f, true);
    //    if (mEffect->getScale().x >= 0.5f) {
    //        is = true;
    //    }
    //}
}

void PlayerMoveComponent::move() {
    int horizontal = Input::horizontal();
    if (!Math::nearZero(horizontal)) {
        mSprite->translate(Vector2(horizontal, 0.f) * MOVE_SPEED);
    }
}

void PlayerMoveComponent::jump() {
    if (!Input::getKeyDown(KeyCode::Space)) {
        return;
    }
    if (mState != PlayerState::OnGround) {
        return;
    }

    //スペースを押していて、地面に立っていたら↓
    mState = PlayerState::JumpNow;
    mCurrentJumpPower = 0.f;
    mX = 0.f;
}

void PlayerMoveComponent::jumpUpdate() {
    if (mState != PlayerState::JumpNow) { //ジャンプ中以外無視
        return;
    }

    //y = ax ^ 2 + bx + c
    //2次関数でジャンプ量調整
    mX += 0.1f;
    mCurrentJumpPower = -Math::pow<float>(mX, 2) + mX + 16.f; //一番右の値がジャンプ量に直結
    mSprite->translate(Vector2(0.f, -mCurrentJumpPower));
}

void PlayerMoveComponent::fall() {
    //重力は常にかける
    mSprite->translate(Vector2(0.f, FALL_SPEED));

    auto sizeY = mSprite->getSize().y * mSprite->getScale().y;
    auto posY = mSprite->getPosition().y;
    if (posY + sizeY + 5.f > Game::WINDOW_HEIGHT) { //無理やり
        mState = PlayerState::OnGround;
    }
}

void PlayerMoveComponent::posClamp() {
    auto pos = mSprite->getPosition();
    auto size = mSprite->getSize() * mSprite->getScale();
    pos.x = Math::clamp<float>(pos.x, 0.f, Game::WINDOW_WIDTH - size.x);
    pos.y = Math::clamp<float>(pos.y, 0.f, Game::WINDOW_HEIGHT - size.y);

    mSprite->setPosition(pos);
}
