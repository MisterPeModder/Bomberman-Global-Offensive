/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"

#include "components/Bomb.hpp"
#include "components/BombNoClip.hpp"
#include "components/Collidable.hpp"
#include "components/Controlable.hpp"
#include "components/Cube.hpp"
#include "components/CubeColor.hpp"
#include "components/Destructible.hpp"
#include "components/Identity.hpp"
#include "components/Living.hpp"
#include "components/Player.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

#include "ecs/Storage.hpp"
#include "ecs/resource/Timer.hpp"

#include "gui/components/Widget.hpp"
#include "logger/Logger.hpp"

#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Vector3.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/textures/Texture2D.hpp"

#include "resources/AssetMap.hpp"
#include "resources/Engine.hpp"
#include "resources/Map.hpp"

#include "systems/Bomb.hpp"
#include "systems/ChangeCube.hpp"
#include "systems/Collision.hpp"
#include "systems/DrawingCube.hpp"
#include "systems/InputManager.hpp"
#include "systems/Movement.hpp"
#include "systems/NoClip.hpp"

#include "game/Engine.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include <cmath>

namespace game
{
    Game::Game(ecs::World &world, Parameters params) : _world(world), _map(params.mapSize), _params(params), _camera()
    {
    }

    const map::Map &Game::getMap() const { return _map; }

    raylib::core::Camera3D const &Game::getCamera() const { return this->_camera; }

    raylib::core::Camera3D &Game::getCamera() { return this->_camera; }

    void Game::setCamera(raylib::core::Camera3D &&camera) { this->_camera = std::move(camera); }

    void Game::setup()
    {
        size_t width = _map.getSize().x;
        size_t depth = _map.getSize().y;

        _camera.setPosition(
            {width / 2.f, 8.f /*static_cast<float>(width)*/, static_cast<float>(depth)}); // Camera position
        _camera.setTarget({width / 2.f, 0.f, depth / 2.f});                               // Camera looking at point
        _camera.setUp({0.0f, 1.0f, 0.0f}); // Camera up vector (rotation towards target)
        _camera.setFovY(75.0f);            // Camera field-of-view Y
        _camera.setProjection(CAMERA_PERSPECTIVE);

        /// Add world resources
        _world.addResource<game::Users>();
        _world.addResource<ecs::Timer>();
        _world.addResource<resources::Map>(_map);
        _world.addResource<resources::Textures>();
        /// Add world storages
        _world.addStorage<components::Bomb>();
        _world.addStorage<game::gui::Widget>();
        /// Add world systems
        _world.addSystem<systems::InputManager>();
        _world.addSystem<systems::ChangeCube>();
        _world.addSystem<systems::DrawingCube>();
        _world.addSystem<systems::Movement>();
        _world.addSystem<systems::Collision>();
        _world.addSystem<systems::DrawBomb>();
        _world.addSystem<systems::ExplodeBomb>();
        _world.addSystem<systems::DisableBombNoClip>();
        /// Setup world systems tags
        _handleInputs.add<systems::InputManager>();
        _update.add<systems::ChangeCube, systems::Movement, systems::ExplodeBomb, systems::DisableBombNoClip>();
        _resolveCollisions.add<systems::Collision>();
        _drawing.add<systems::DrawingCube, systems::DrawBomb>();

        for (size_t i = 0; i < _params.playerCount; i++) {
            User::UserId owner = static_cast<User::UserId>(i);
            raylib::core::Vector2u cell = _map.getPlayerStartingPosition(owner);

            _world.addEntity()
                .with<components::Position>(static_cast<float>(cell.x), 1.f, static_cast<float>(cell.y))
                .with<components::Velocity>()
                .with<components::Living>(_params.livesCount)
                .with<components::Collidable>()
                .with<components::Player>()
                .with<components::Cube>()
                .with<components::Size>(0.7f, 2.f, 0.7f)
                .with<components::CubeColor>(raylib::core::Color::RED)
                .with<components::Controlable>(owner, components::Player::handleActionEvent)
                .with<components::BombNoClip>()
                .with<components::Identity>()
                .build();
        }

        /// Ground
        _world.addEntity()
            .with<components::Position>(width / 2.f - 0.5f, 0.f, depth / 2.f - 0.5f)
            .with<components::Size>(static_cast<float>(width), 0.1f, static_cast<float>(depth))
            .with<components::CubeColor>(raylib::core::Color::RAY_WHITE)
            .with<components::Cube>()
            .build();

        /// Walls, crates
        for (float z = -1; static_cast<float>(z) < depth + 1; z++) {
            for (float x = -1; static_cast<float>(x) < width + 1; x++) {
                bool wall = false;
                bool destructible = false;
                raylib::core::Color color = raylib::core::Color(40, 40, 40);

                if (z == -1 || x == -1 || z == depth || x == width)
                    wall = true;
                else {
                    switch (_map.getElement({static_cast<unsigned int>(x), static_cast<unsigned int>(z)})) {
                        case map::Map::Element::Crate:
                            wall = true;
                            destructible = true;
                            color = raylib::core::Color(110, 85, 70);
                            break;
                        case map::Map::Element::Wall: wall = true; break;
                        default: break;
                    }
                }
                if (wall) {
                    auto builder = _world.addEntity();

                    (void)builder.with<components::Position>(x, 0.5f, z)
                        .with<components::Collidable>()
                        .with<components::Wall>()
                        .with<components::Cube>()
                        .with<components::Size>(1.f, 1.f, 1.f)
                        .with<components::CubeColor>(color);
                    if (destructible)
                        (void)builder.with<components::Destructible>();
                    builder.build();
                }
            }
        }
    }

    void Game::drawFrame()
    {
        _camera.update();

        _world.runSystems(_handleInputs);
        _world.runSystems(_update);
        _world.runSystems(_resolveCollisions);

        raylib::core::scoped::Drawing drawing;
        raylib::core::Window::clear();
        {
            raylib::core::scoped::Mode3D mode3D(_camera);
            _world.runSystems(_drawing);
            // if (rand()%100 == 1)
            //     _world.getResource<resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
        };
        raylib::core::Window::drawFPS(10, 10);
        _world.maintain();
    }
} // namespace game
