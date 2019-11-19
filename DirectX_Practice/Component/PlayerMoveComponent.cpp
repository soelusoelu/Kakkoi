#include "PlayerMoveComponent.h"
#include "../Actor/Actor.h"
#include "../Actor/AvoidancePlayerActor.h"
#include "../Actor/ComponentManagementOfActor.h"
#include "../Actor/PlayerActor.h"
#include "../Actor/PlayerAttack.h"
#include "../Actor/SpecialAttack.h"
#include "../Component/CircleCollisionComponent.h"
#include "../Component/DamageComponent.h"
#include "../Component/HitPointComponent.h"
#include "../Component/SPComponent.h"
#include "../Device/Time.h"
#include "../UI/Sprite.h"
#include "../Component/SpriteComponent.h"
#include "../System/Game.h"
#include "../Utility/Input.h"
#include "../Utility/Math.h"

PlayerMoveComponent::PlayerMoveComponent(Actor* owner, int updateOrder) :
    Component(owner, updateOrder),
    mSprite(nullptr),
    mCircle(nullptr),
    mHP(nullptr),
    mSP(nullptr),
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
    mSprite->setPosition(Vector2(Game::WINDOW_WIDTH / 2.f, Game::WINDOW_HEIGHT - (mSprite->getTextureSize().y * mSprite->getScale().y)));

    mCircle = mOwner->getComponentManager()->getComponent<CircleCollisionComponent>();
    mHP = mOwner->getComponentManager()->getComponent<HitPointComponent>();
    mSP = mOwner->getComponentManager()->getComponent<SPComponent>();
    mSP->set(0);
    mSP->setMax(300);
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
    specialAttack();
    hit();
}

void PlayerMoveComponent::move() {
    int horizontal = Input::horizontal();
    if (!Math::nearZero(horizontal)) {
        mSprite->translate(Vector2(horizontal, 0.f) * MOVE_SPEED * AvoidancePlayerActor::slow());

        mDir = horizontal < 0 ? Direction::Left : Direction::Right;
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
    mCurrentJumpPower = -3 * Math::pow<float>(mX, 2) + mX + 16.f; //一番右の値がジャンプ量に直結
    mSprite->translate(Vector2(0.f, -mCurrentJumpPower));
}

void PlayerMoveComponent::fall() {
    //重力は常にかける
    mSprite->translate(Vector2(0.f, FALL_SPEED * AvoidancePlayerActor::slow()));

    auto sizeY = mSprite->getScreenTextureSize().y;
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
        pos.x -= AVOIDANCE_LENGTH - mSprite->getScreenTextureSize().x;
    }
    auto scale = mSprite->getScale();
    scale.x = AVOIDANCE_LENGTH / mSprite->getTextureSize().x;
    new AvoidancePlayerActor(
        dynamic_cast<PlayerActor*>(mOwner),
        pos,
        mSprite->fileName(),
        mSprite->getTextureSize(),
        scale
    );

    mCircle->disabled();
}

void PlayerMoveComponent::posClamp() {
    auto pos = mSprite->getPosition();
    auto size = mSprite->getScreenTextureSize();
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

    auto sp = mSP->sp() / 101;
    int attackRatio = 0;
    switch (sp) {
    case 0: attackRatio = 100; break;
    case 1: attackRatio = 120; break;
    case 2: attackRatio = 135; break;
    default: break;
    }
    new PlayerAttack(pos, attackRatio);
    mCanAttack = false;
}

void PlayerMoveComponent::specialAttack() {
    if (!Input::getKeyDown(KeyCode::Q)) {
        return;
    }
    auto sp = mSP->sp();
    if (sp != 100 && sp != 200 && sp != 300) {
        return;
    }

    auto spRaito = sp / 100;
    int attackRatio = 0;
    switch (spRaito) {
    case 1: attackRatio = 100; break;
    case 2: attackRatio = 150; break;
    case 3: attackRatio = 200; break;
    default: break;
    }
    new SpecialAttack(dynamic_cast<PlayerActor*>(mOwner), attackRatio);
    mSP->use(199);
}

void PlayerMoveComponent::hit() {
    if (!mCircle->getEnable()) {
        mCircle->enabled();
        return;
    }

    auto col = mCircle->onCollisionEnter();
    for (auto&& c : col) {
        if (c->getOwner()->getTag() != "EnemyBullet") {
            continue;
        }
        if (AvoidancePlayerActor::mSuccessedAvoidance) {
            continue;
        }

        auto damage = c->getOwner()->getComponentManager()->getComponent<DamageComponent>();
        mHP->takeDamage(damage->damage());
    }
}
