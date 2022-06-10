/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include "map/Map.hpp"
#include "raylib/core/Vector2.hpp"

namespace game
{
    class Game {
      public:
        struct Parameters {
            size_t playerCount;
            size_t livesCount;
            raylib::core::Vector2 mapSize;

            Parameters(size_t pplayerCount = 1, size_t plivesCount = 1, raylib::core::Vector2 pmapSize = {13.f, 13.f})
                : playerCount(pplayerCount), livesCount(plivesCount), mapSize(pmapSize)
            {
            }
        };

        Game(Parameters params = Parameters());
        ~Game() = default;

        void update(float dt);
        const map::Map &getMap() const;

      private:
        map::Map _map;
        Parameters _params;
    };
} // namespace game

#endif /* !GAME_HPP_ */
