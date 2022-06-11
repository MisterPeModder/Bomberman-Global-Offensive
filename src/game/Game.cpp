/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"
#include "game/worlds/Worlds.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    Game::Game(ecs::World &world, Parameters params) : _world(world), _map(params.mapSize), _params(params) {}

    const map::Map &Game::getMap() const { return _map; }

    void Game::setup(raylib::core::Camera3D &camera)
    {
        size_t width = _map.getSize().x;
        size_t depth = _map.getSize().y;

        camera.setPosition(
            {width / 2.f, 8.f /*static_cast<float>(width)*/, static_cast<float>(depth)}); // Camera position
        camera.setTarget({width / 2.f, 0.f, depth / 2.f});                              // Camera looking at point
        camera.setUp({0.0f, 1.0f, 0.0f}); // Camera up vector (rotation towards target)
        camera.setFovY(75.0f);            // Camera field-of-view Y
        camera.setProjection(CAMERA_PERSPECTIVE);

        loadGameWorld();
    }

    void Game::drawFrame(const raylib::core::Camera3D &camera)
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
