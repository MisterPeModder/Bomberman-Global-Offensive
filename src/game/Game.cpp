/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#include "Game.hpp"

namespace game
{
    Game::Game(Parameters params)
        : _map(static_cast<size_t>(params.mapSize.x), static_cast<size_t>(params.mapSize.y)), _params(params)
    {
    }

    void Game::update(float dt) { (void)dt; }

    const map::Map &Game::getMap() const { return _map; }
} // namespace game