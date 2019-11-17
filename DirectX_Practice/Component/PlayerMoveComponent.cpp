#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerAttack.h"
#include "../Device/Time.h"
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
    AVOIDANCE_LENGTH(150),
    mAttackTimer(std::make_unique<Time>(0.25f)),
    mCanAttack(true),
    mState(PlayerState::OnGround),
    mDir(Direction::Right) {
}

PlayerMoveComponent::~PlayerMoveComponent() = default;

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
    avoidance();
    posClamp();
    canAttack();
    attack();
}

void PlayerMoveComponent::move() {
    int horizontal = Input::horizontal();
    if (!Math::nearZero(horizontal)) {
        mSprite->translate(Vector2(horizontal, 0.f) * MOVE_SPEED);

        if (horizontal < 0) {
            mDir = Direction::Left;
        } else if (horizontal > 0) {
            mDir = Direction::Right;
        }
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
    mState = PlayerState::Jump;
    mCurrentJumpPower = 0.f;
    mX = 0.f;
}

void PlayerMoveComponent::jumpUpdate() {
    if (mState != PlayerState::Jump) { //ジャンプ中以外無視
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

void PlayerMoveComponent::avoidance() {
    if (!Input::getKeyDown(KeyCode::X)) {
        return;
    }

    auto pos = mSprite->getPosition();
    auto l = mDir == Direction::Left ? -AVOIDANCE_LENGTH : AVOIDANCE_LENGTH;
    mSprite->translate(Vector2(l, 0.f));

    if (l < 0) {
        pos.x -= AVOIDANCE_LENGTH / 2.f;
    }
    auto scale = mSprite->getScale();
    scale.x = AVOIDANCE_LENGTH / mSprite->getSize().x;
    new AvoidancePlayerActor(pos, mSprite->fileName(), mSprite->getSize(), scale);
}

void PlayerMoveComponent::posClamp() {
    auto pos = mSprite->getPosition();
    auto size = mSprite->getSize() * mSprite->getScale();
    pos.x = Math::clamp<float>(pos.x, 0.f, Game::WINDOW_WIDTH - size.x);
    pos.y = Math::clamp<float>(pos.y, 0.f, Game::WINDOW_HEIGHT - size.y);

    mSprite->setPosition(pos);
}

void PlayerMoveComponent::canAttack() {
    if (mCanAttack) {
        return;
    }

    mAttackTimer->update();
    if (mAttackTimer->isTime()) {
        mAttackTimer->reset();
        mCanAttack = true;
    }
}

void PlayerMoveComponent::attack() {
    if (!Input::getKeyDown(KeyCode::Z)) {
        return;
    }
    if (!mCanAttack) {
        return;
    }
    Vector2 pos = mSprite->getPosition();
    if (mDir == Direction::Left) {
        pos += Vector2(-96.f, -32.f);
    } else {
        pos += Vector2(64.f, -32.f);
    }
    new PlayerAttack(pos);
    mCanAttack = false;
}
