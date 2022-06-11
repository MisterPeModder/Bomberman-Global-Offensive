/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameWorld
*/

#include "Worlds.hpp"
#include "ecs/Entity.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/resource/Timer.hpp"
#include "game/Game.hpp"
#include "raylib/core/Color.hpp"
#include "util/util.hpp"

#include "components/Collidable.hpp"
#include "components/Controlable.hpp"
#include "components/Cube.hpp"
#include "components/CubeColor.hpp"
#include "components/Destructible.hpp"
#include "components/Living.hpp"
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "game/components/Cube.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"

#include "game/systems/Cube.hpp"
#include "game/systems/Model.hpp"
#include "systems/ChangeCube.hpp"
#include "systems/Collision.hpp"
#include "systems/DrawingCube.hpp"
#include "systems/InputManager.hpp"
#include "systems/Movement.hpp"

namespace game
{
    void Game::loadGameWorld()
    {
        size_t width = _map.getSize().x;
        size_t depth = _map.getSize().y;

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
} // namespace game
