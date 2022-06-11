/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera3D
*/

#include "Camera3D.hpp"

namespace raylib
{
    namespace core
    {
        Camera3D::Camera3D()
        {
            _camera.position = {0.f, 10.f, 10.f};
            _camera.target = {0.f, 0.f, 0.f};
            _camera.up = {0.f, 1.f, 0.f};
            _camera.fovy = 45.f;
            _camera.projection = CAMERA_PERSPECTIVE;
        }

        Camera3D::~Camera3D() {}

        Camera3D::Camera3D(Camera3D &&camera) : _camera(camera._camera) {}

        Camera3D &Camera3D::operator=(Camera3D &&camera)
        {
            _camera = camera._camera;
            return *this;
        }

        void Camera3D::begin3D() { BeginMode3D(_camera); }

        void Camera3D::end3D() { EndMode3D(); }

        Vector3f Camera3D::getPosition() const { return {_camera.position.x, _camera.position.y, _camera.position.z}; }

        void Camera3D::setPosition(Vector3f position) { _camera.position = {position.x, position.y, position.z}; }

        Vector3f Camera3D::getTarget() const { return {_camera.target.x, _camera.target.y, _camera.target.z}; }

        void Camera3D::setTarget(Vector3f target) { _camera.target = {target.x, target.y, target.z}; }

        Vector3f Camera3D::getUp() const { return {_camera.up.x, _camera.up.y, _camera.up.z}; }

        void Camera3D::setUp(Vector3f up) { _camera.up = {up.x, up.y, up.z}; }

        float Camera3D::getFovY() const { return _camera.fovy; }

        void Camera3D::setFovY(float fovY) { _camera.fovy = fovY; }

        int Camera3D::getProjection() const { return _camera.projection; }

        void Camera3D::setProjection(int projection) { _camera.projection = projection; }

        void Camera3D::setMode(CameraMode mode) { SetCameraMode(_camera, mode); }

        void Camera3D::update() { UpdateCamera(&_camera); }

    } // namespace core
} // namespace raylib
