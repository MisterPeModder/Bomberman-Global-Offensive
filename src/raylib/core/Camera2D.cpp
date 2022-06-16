/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera2D
*/

#include "Camera2D.hpp"

namespace raylib
{
    namespace core
    {
        Camera2D::Camera2D()
        {
            _camera.offset = {0.f, 0.f};
            _camera.target = {0.f, 0.f};
            _camera.rotation = 0.f;
            _camera.zoom = 1.f;
        }

        Camera2D::~Camera2D() {}

        Camera2D::Camera2D(Camera2D &&camera) : _camera(camera._camera) {}

        Camera2D &Camera2D::operator=(Camera2D &&camera)
        {
            _camera = camera._camera;
            return *this;
        }

        void Camera2D::begin2D() const { BeginMode2D(_camera); }

        void Camera2D::end2D() { EndMode2D(); }

        Vector2f Camera2D::getOffset() const { return {_camera.offset.x, _camera.offset.y}; }

        void Camera2D::setOffset(Vector2f offset) { _camera.offset = {offset.x, offset.y}; }

        Vector2f Camera2D::getTarget() const { return {_camera.target.x, _camera.target.y}; }

        void Camera2D::setTarget(Vector2f target) { _camera.target = {target.x, target.y}; }

        float Camera2D::getRotation() const { return _camera.rotation; }

        void Camera2D::setRotation(float rotation) { _camera.rotation = rotation; }

        float Camera2D::getZoom() const { return _camera.zoom; }

        void Camera2D::setZoom(float zoom) { _camera.zoom = zoom; }
    } // namespace core
} // namespace raylib
