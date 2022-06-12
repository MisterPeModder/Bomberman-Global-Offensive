/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** AWorld
*/

#include "game/worlds/AWorld.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"

namespace game
{
    AWorld::AWorld(ecs::World &world) : _world(world) {}

    AWorld::~AWorld() { _world.clear(); }

    void AWorld::setCamera(raylib::core::Camera3D &camera) {}

    void AWorld::drawFrame(const raylib::core::Camera3D &camera)
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
