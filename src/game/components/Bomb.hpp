/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#ifndef GAME_COMPONENTS_BOMB_HPP_
#define GAME_COMPONENTS_BOMB_HPP_

#include <chrono>
#include "ecs/Component.hpp"

namespace game::components
{
    struct Bomb : public ecs::Component {
        std::chrono::steady_clock::time_point placedTime;
        size_t radius;
        std::chrono::milliseconds explosionDelay;
        bool exploded;

        Bomb(size_t pRadius = 1, std::chrono::milliseconds pExplosionDelay = std::chrono::milliseconds(2000))
            : placedTime(std::chrono::steady_clock::now()), radius(pRadius), explosionDelay(pExplosionDelay),
              exploded(false){};
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_BOMB_HPP_ */
