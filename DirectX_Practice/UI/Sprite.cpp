#include "Sprite.h"
#include "SpriteManager.h"
#include "Texture.h"
#include "../Device/Renderer.h"
#include <cassert>

Sprite::Sprite(const std::string& fileName, const Vector2& size, float z) :
    DEFAULT_SIZE(size),
    mSize(size),
    mPosition(Vector2::zero, z),
    mRotation(Quaternion::identity),
    mScale(Vector2::one),
    mColor(ColorPalette::white, 1.f),
    mUV(0.f, 0.f, 1.f, 1.f),
    mPivot(mSize / 2.f),
    mWorld(Matrix4::identity),
    mState(SpriteState::Active),
    mTexture(Renderer::getTexture(fileName)),
    mWorldUpdateFlag(true) {

    SpriteManager::add(this);
}

Sprite::~Sprite() = default;

Sprite::Sprite(const Sprite & sprite) :
    DEFAULT_SIZE(DEFAULT_SIZE),
    mSize(sprite.getSize()),
    mPosition(Vector3(sprite.getPosition(), sprite.getDepth())),
    mRotation(sprite.getRotation()),
    mScale(sprite.getScale()),
    mColor(sprite.getColor()),
    mUV(sprite.getUV()),
    mPivot(sprite.getPivot()),
    mWorld(sprite.getWorld()),
    mState(SpriteState::Active),
    mTexture(sprite.getTexture()),
    mWorldUpdateFlag(true) {
}

void Sprite::update() {
    updateWorld();
}

Sprite* Sprite::draw() const {
    auto s = new Sprite(*this);
    SpriteManager::add(s);
    s->mState = SpriteState::Once;
    return s;
}

void Sprite::setPosition(const Vector2 & pos) {
    mPosition.x = pos.x;
    mPosition.y = pos.y;
    mWorldUpdateFlag = true;
}

void Sprite::setPrimary(float z) {
    mPosition.z = z;
    mWorldUpdateFlag = true;
    mZSortFlag = true;
}

const Vector2& Sprite::getPosition() const {
    return Vector2(mPosition.x, mPosition.y);
}

const float Sprite::getDepth() const {
    return mPosition.z;
}

void Sprite::translate(const Vector2 & translation) {
    mPosition.x += translation.x;
    mPosition.y += translation.y;
    mWorldUpdateFlag = true;
}

void Sprite::setRotation(float angle) {
    angle *= 0.5f * Math::deg2Rad;
    float sinAngle = Math::sin(angle);

    mRotation.z *= sinAngle;
    mRotation.w = Math::cos(angle);

    mWorldUpdateFlag = true;
}

const Quaternion& Sprite::getRotation() const {
    return mRotation;
}

void Sprite::rotate(float angle) {
    angle *= 0.5f * Math::deg2Rad;
    float sinAngle = Math::sin(angle);

    Quaternion inc;
    inc.z = sinAngle;
    inc.w = Math::cos(angle);

    mRotation = Quaternion::concatenate(mRotation, inc);

    mWorldUpdateFlag = true;
}

void Sprite::setScale(const Vector2 & scale, bool isCenterShift) {
    bool isBigger = mScale.x < scale.x;

    if (isCenterShift) {
        centerShift(scale);
    }

    mScale = scale;

    //ピボット修正
    mPivot = mSize / 2.f;
    mPivot.x *= mScale.x;
    mPivot.y *= mScale.y;

    mWorldUpdateFlag = true;
}

void Sprite::setScale(float scale, bool isCenterShift) {
    if (isCenterShift) {
        centerShift(Vector2(scale, scale));
    }

    mScale.x = scale;
    mScale.y = scale;

    //ピボット修正
    mPivot = mSize / 2.f;
    mPivot.x *= mScale.x;
    mPivot.y *= mScale.y;

    mWorldUpdateFlag = true;
}

const Vector2& Sprite::getScale() const {
    return mScale;
}

void Sprite::setColor(const Vector3 & color) {
    mColor.x = color.x;
    mColor.y = color.y;
    mColor.z = color.z;
    mWorldUpdateFlag = true;
}

void Sprite::setColor(float r, float g, float b) {
    mColor.x = r;
    mColor.y = g;
    mColor.z = b;
    mWorldUpdateFlag = true;
}

void Sprite::setAlpha(float alpha) {
    mColor.w = alpha;
    mWorldUpdateFlag = true;
}

const Vector4& Sprite::getColor() const {
    return mColor;
}

void Sprite::setUV(float l, float t, float r, float b) {
    assert(0.f <= l || l <= 1.f);
    assert(0.f <= t || t <= 1.f);
    assert(l <= r || r <= 1.f);
    assert(t <= b || b <= 1.f);

    mUV.x = l;
    mUV.y = t;
    mUV.z = r;
    mUV.w = b;

    //サイズ修正
    mSize.x = DEFAULT_SIZE.x * (r - l);
    mSize.y = DEFAULT_SIZE.y * (b - t);

    //ピボット修正
    mPivot = mSize / 2.f;
    mPivot.x *= mScale.x;
    mPivot.y *= mScale.y;

    mWorldUpdateFlag = true;
}

const Vector4& Sprite::getUV() const {
    return mUV;
}

void Sprite::setPivot(const Vector2 & pivot) {
    mPivot = pivot;
    mWorldUpdateFlag = true;
}

const Vector2& Sprite::getPivot() const {
    return mPivot;
}

const Vector2& Sprite::getSize() const {
    return mSize;
}

void Sprite::destroy(Sprite * sprite) {
    sprite->mState = SpriteState::Dead;
}

void Sprite::destroy(std::shared_ptr<Sprite> sprite) {
    sprite->mState = SpriteState::Dead;
}

const SpriteState Sprite::getState() const {
    return mState;
}

const Matrix4& Sprite::getWorld() const {
    return mWorld;
}

const std::shared_ptr<Texture> Sprite::getTexture() const {
    return mTexture;
}

bool Sprite::getWorldUpdateFlag() const {
    return mWorldUpdateFlag;
}

void Sprite::onceToDead() {
    if (mState == SpriteState::Once) {
        mState = SpriteState::Dead;
    }
}

void Sprite::updateWorld() {
    //ワールド行列に変更が生じたら
    if (!mWorldUpdateFlag) {
        return;
    }
    mWorldUpdateFlag = false;

    mWorld = Matrix4::createScale(mSize.x * mScale.x, mSize.y * mScale.y, 1.f);
    mWorld *= Matrix4::createTranslation(Vector3(-mPivot, 0.f));
    mWorld *= Matrix4::createFromQuaternion(mRotation);
    mWorld *= Matrix4::createTranslation(mPosition + Vector3(mPivot, 0.f));
}

void Sprite::centerShift(const Vector2& nextScale) {
    Vector2 shift;
    Vector2 PreviosSize = mSize * mScale;
    auto nextSize = mSize * nextScale;
    shift = (PreviosSize - nextSize) / 2.f;
    //if (isbigger) {
    //    shift *= -1;
    //}

    translate(shift);
}

bool Sprite::mZSortFlag = false;
