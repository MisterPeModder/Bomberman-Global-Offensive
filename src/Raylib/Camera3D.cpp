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

void raylib::Camera3D::begin3D()
{
    BeginMode3D(_camera);
}

void raylib::Camera3D::end3D()
{
    EndMode3D();
}

Vector3 raylib::Camera3D::getPosition() const
{
    return _camera.position;
}

void raylib::Camera3D::setPosition(Vector3 position)
{
    _camera.position = position;
}

Vector3 raylib::Camera3D::getTarget() const
{
    return _camera.target;
}

void raylib::Camera3D::setTarget(Vector3 target)
{
    _camera.target = target;
}

Vector3 raylib::Camera3D::getUp() const
{
    return _camera.up;
}

void raylib::Camera3D::setUp(Vector3 up)
{
    _camera.up = up;
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
