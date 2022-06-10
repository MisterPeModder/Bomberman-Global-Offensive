/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"
#include "components/Collidable.hpp"
#include "components/Controlable.hpp"
#include "components/Destructible.hpp"
#include "components/Living.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "ecs/resource/Timer.hpp"
#include "game/systems/InputManager.hpp"

#include "game/components/Cube.hpp"
#include "game/components/CubeColor.hpp"
#include "game/systems/ChangeCube.hpp"
#include "game/systems/Collision.hpp"
#include "game/systems/DrawingCube.hpp"
#include "game/systems/Movement.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/scoped.hpp"

namespace game
{
    Game::Game(ecs::World &world, Parameters params)
        : _world(world), _map(static_cast<size_t>(params.mapSize.x), static_cast<size_t>(params.mapSize.y)),
          _params(params)
    {
    }

    const map::Map &Game::getMap() const { return _map; }

    void Game::setup(raylib::core::Camera3D &camera)
    {
        size_t width = _map.getWidth();
        size_t depth = _map.getHeight();

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
        _world.addSystem<game::InputManager>();
        _world.addSystem<ChangeCube>();
        _world.addSystem<DrawingCube>();
        _world.addSystem<Movement>();
        _world.addSystem<Collision>();

        for (size_t i = 0; i < _params.playerCount; i++) {
            User::UserId owner = static_cast<User::UserId>(i);
            Vector2 cell = _map.getPlayerStartingPosition(owner);

            _world.addEntity()
                .with<Position>(cell.x, 1.f, cell.y)
                .with<Velocity>()
                .with<Living>(_params.livesCount)
                .with<Collidable>()
                .with<Player>()
                .with<Cube>()
                .with<Size>(0.7f, 2.f, 0.7f)
                .with<CubeColor>(raylib::core::Color::RED)
                .with<Controlable>(owner,
                    [this](ecs::Entity self, ecs::SystemData data, const Users::ActionEvent &event) {
                        if (isMoveAction(event.action)) {
                            auto &velocity = _world.getStorage<Velocity>()[self.getId()];
                            auto &user = _world.getResource<Users>()[event.user];
                            GameAction bestAction;
                            float value = 0.f;
                            float speed = 4.f;

                            for (size_t i = static_cast<size_t>(GameAction::MOVE_LEFT);
                                 i <= static_cast<size_t>(GameAction::MOVE_DOWN); i++) {
                                GameAction current = static_cast<GameAction>(i);
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
                                }
                            return true;
                        }
                        return false;
                    })
                .build();
        }

        /// Ground
        _world.addEntity()
            .with<Position>(width / 2.f - 0.5f, 0.f, depth / 2.f - 0.5f)
            .with<Size>(static_cast<float>(width), 0.1f, static_cast<float>(depth))
            .with<CubeColor>(raylib::core::Color::RAY_WHITE)
            .with<Cube>()
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
                    switch (_map.getElement(x, z)) {
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
                                        .with<Position>(x, 0.5f, z)
                                        .with<Collidable>()
                                        .with<Wall>()
                                        .with<Cube>()
                                        .with<Size>(1.f, 1.f, 1.f)
                                        .with<CubeColor>(color);
                    if (destructible)
                        builder.with<Destructible>().build();
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