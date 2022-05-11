/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Camera3D
*/

#include "Camera3D.hpp"

raylib::Camera3D::Camera3D()
{
    _camera.position = {0.f, 10.f, 10.f};
    _camera.target = {0.f, 0.f, 0.f};
    _camera.up = {0.f, 1.f, 0.f};
    _camera.fovy = 45.f;
    _camera.projection = CAMERA_PERSPECTIVE;
}

raylib::Camera3D::~Camera3D()
{
}

raylib::Camera3D::Camera3D(Camera3D&& camera)
 : _camera(camera._camera)
{
}

raylib::Camera3D &raylib::Camera3D::operator=(Camera3D&& camera)
{
    _camera = camera._camera;
    return *this;
}

void raylib::Camera3D::begin3D()
{
    BeginMode3D(_camera);
}

void raylib::Camera3D::end3D()
{
    EndMode3D();
}

raylib::Vector3 raylib::Camera3D::getPosition() const
{
    return {_camera.position.x, _camera.position.y, _camera.position.z};
}

void raylib::Camera3D::setPosition(raylib::Vector3 position)
{
    _camera.position = {position.getX(), position.getY(), position.getZ()};
}

raylib::Vector3 raylib::Camera3D::getTarget() const
{
    return {_camera.target.x, _camera.target.y, _camera.target.z};
}

void raylib::Camera3D::setTarget(raylib::Vector3 target)
{
    _camera.target = {target.getX(), target.getY(), target.getZ()};
}

raylib::Vector3 raylib::Camera3D::getUp() const
{
    return {_camera.up.x, _camera.up.y, _camera.up.z};
}

void raylib::Camera3D::setUp(raylib::Vector3 up)
{
    _camera.up = {up.getX(), up.getY(), up.getZ()};
}

float raylib::Camera3D::getFovy() const
{
    return _camera.fovy;
}

void raylib::Camera3D::setFovy(float fovy)
{
    _camera.fovy = fovy;
}

int raylib::Camera3D::getProjection() const
{
    return _camera.projection;
}

void raylib::Camera3D::setProjection(int projection)
{
    _camera.projection = projection;
}
