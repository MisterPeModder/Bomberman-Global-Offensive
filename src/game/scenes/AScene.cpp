/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** AScene
*/

#include "game/scenes/AScene.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"

namespace game
{
    AScene::AScene() {}

    AScene::~AScene()
    { /* _world.clear(); */
    }

    void AScene::setCamera(raylib::core::Camera3D &camera)
    {
        camera.setMode(raylib::core::Camera3D::CameraMode::CUSTOM);
    }

    void AScene::drawFrame(const raylib::core::Camera3D &camera)
    {
        raylib::core::scoped::Drawing drawing;
        raylib::core::Window::clear();
        {
            raylib::core::scoped::Mode3D mode3D(camera);
            _world.runSystems();
        };
        raylib::core::Window::drawFPS(10, 10);
    }
} // namespace game
