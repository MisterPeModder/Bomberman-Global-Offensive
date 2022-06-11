/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"
#include "ecs/resource/Timer.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/scoped.hpp"

#include "components/Collidable.hpp"
#include "components/Controlable.hpp"
#include "components/Cube.hpp"
#include "components/CubeColor.hpp"
#include "components/Destructible.hpp"
#include "components/Living.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"

#include "systems/ChangeCube.hpp"
#include "systems/Collision.hpp"
#include "systems/DrawingCube.hpp"
#include "systems/InputManager.hpp"
#include "systems/Movement.hpp"

namespace game
{
    Game::Game(ecs::World &world, Parameters params) : _world(world), _map(params.mapSize), _params(params) {}

    const map::Map &Game::getMap() const { return _map; }

    void Game::setup(raylib::core::Camera3D &camera)
    {
        size_t width = _map.getSize().x;
        size_t depth = _map.getSize().y;

        camera.setPosition(
            {width / 2.f, 8 /*static_cast<float>(width)*/, static_cast<float>(depth)}); // Camera position
        camera.setTarget({width / 2.f, 0.f, depth / 2.f});                              // Camera looking at point
        camera.setUp({0.0f, 1.0f, 0.0f}); // Camera up vector (rotation towards target)
        camera.setFovY(75.0f);            // Camera field-of-view Y
        camera.setProjection(CAMERA_PERSPECTIVE);

        /// Add world ressources
        _world.addResource<game::Users>();
        _world.addResource<ecs::Timer>();
        /// Add world systems
        _world.addSystem<systems::InputManager>();
        _world.addSystem<systems::ChangeCube>();
        _world.addSystem<systems::DrawingCube>();
        _world.addSystem<systems::Movement>();
        _world.addSystem<systems::Collision>();

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
                .with<components::Controlable>(owner,
                    [this](ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) {
                        (void)data;
                        if (isMoveAction(event.action)) {
                            auto &velocity = _world.getStorage<components::Velocity>()[self.getId()];
                            auto &user = _world.getResource<Users>()[event.user];
                            GameAction bestAction = GameAction::NONE;
                            float value = 0.f;
                            float speed = 4.f;

                            for (size_t j = static_cast<size_t>(GameAction::MOVE_LEFT);
                                 j <= static_cast<size_t>(GameAction::MOVE_DOWN); j++) {
                                GameAction current = static_cast<GameAction>(j);
                                if (user.getActionValue(current) > value) {
                                    bestAction = current;
                                    value = user.getActionValue(current);
                                }
                            }
                            if (value < 0.2f)
                                velocity = {0.f, 0.f};
                            else
                                switch (bestAction) {
                                    case GameAction::MOVE_LEFT: velocity = {-speed, 0.f, 0.f}; break;
                                    case GameAction::MOVE_UP: velocity = {0.f, 0.f, -speed}; break;
                                    case GameAction::MOVE_RIGHT: velocity = {speed, 0.f, 0.f}; break;
                                    case GameAction::MOVE_DOWN: velocity = {0.f, 0.f, speed}; break;
                                    default: break;
                                }
                            return true;
                        }
                        return false;
                    })
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
                    auto &builder = _world.addEntity()
                                        .with<components::Position>(x, 0.5f, z)
                                        .with<components::Collidable>()
                                        .with<components::Wall>()
                                        .with<components::Cube>()
                                        .with<components::Size>(1.f, 1.f, 1.f)
                                        .with<components::CubeColor>(color);
                    if (destructible)
                        builder.with<components::Destructible>().build();
                    else
                        builder.build();
                }
            }
        }
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
