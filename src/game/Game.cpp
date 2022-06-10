/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"
#include "components/Collidable.hpp"
#include "components/Destructible.hpp"
#include "components/Living.hpp"
#include "components/Movable.hpp"
#include "components/Position.hpp"

namespace game
{
    Game::Game(ecs::World &world, Parameters params)
        : _world(world), _map(static_cast<size_t>(params.mapSize.x), static_cast<size_t>(params.mapSize.y)),
          _params(params)
    {
    }

    void Game::run()
    {
        for (size_t i = 0; i < _params.playerCount; i++) {
            _world.addEntity()
                .with<Position>(_map.getPlayerStartingPosition(static_cast<User::UserId>(i)))
                .with<Movable>()
                .with<Living>(_params.livesCount)
                .with<Collidable>()
                .build();
        }

        for (float z = -1; static_cast<float>(z) < _map.getHeight() + 1; z++) {
            for (float x = -1; static_cast<float>(x) < _map.getWidth() + 1; x++) {
                bool wall = false;
                bool destructible = false;

                if (z == -1 || x == -1 || z == _map.getHeight() || x == _map.getWidth())
                    wall = true;
                else
                    switch (_map.getElement()) {
                        case map::Map::Element::Crate:
                            wall = true;
                            destructible = true;
                            break;
                        case map::Map::Element::Wall: wall = true; break;
                        default: break;
                    }
                if (wall) {
                    auto builder = _world.addEntity().with<Position>(x, 0.f, z).with<Collidable>().with<Wall>();
                    if (destructible)
                        builder.with<Destructible>();
                    builder.build();
                }
            }
        }
    }

} // namespace game