#include "Camera.h"
#include "../Actor/PlayerActor.h"
#include "../Component/TransformComponent.h"
#include "../System/Game.h"

Camera::Camera() :
    mCameraPosition(Vector3::zero),
    mLookAt(Vector3::zero),
    mUp(Vector3::up),
    mPlayerPosition(mCameraPosition),
    mView(Matrix4::identity),
    mProj(Matrix4::identity) {
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
    mProj = Matrix4::createPerspectiveFOV(
        45.f,
        static_cast<float>(Game::WINDOW_WIDTH),
        static_cast<float>(Game::WINDOW_HEIGHT),
        0.1f,
        1000.f
    );
}

Camera::~Camera() = default;

void Camera::update(std::shared_ptr<PlayerActor> player) {
    if (player) {
        Vector3 eyeVec = player->getTransform()->forward();

        mCameraPosition = Vector3(
            player->getTransform()->getPosition().x + eyeVec.x * 7.f,
            player->getTransform()->getPosition().y + 2.f,
            player->getTransform()->getPosition().z - eyeVec.z * 5.f
        );
        mPlayerPosition = player->getTransform()->getPosition();
        mLookAt = Vector3(mPlayerPosition.x, mPlayerPosition.y + 1.5f, mPlayerPosition.z + 3.f); //注視点
    }

    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
}

void Camera::update() {
    mView = Matrix4::createLookAt(mCameraPosition, mLookAt, mUp);
}

Vector3 Camera::getPosition() {
    return mCameraPosition;
}

Matrix4 Camera::getView() {
    return mView;
}

Matrix4 Camera::getProjection() {
    return mProj;
}
