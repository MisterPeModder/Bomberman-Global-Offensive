/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#ifndef GAME_COMPONENTS_BOMB_HPP_
#define GAME_COMPONENTS_BOMB_HPP_

#include <chrono>
#include "Position.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"

namespace game::components
{
    /// Bomb component
    struct Bomb : public ecs::Component {
        /// Time when the bomb was placed
        std::chrono::steady_clock::time_point placedTime;
        /// Radius of the bomb explosion
        size_t radius;
        /// Delay before the explosion
        std::chrono::milliseconds explosionDelay;
        /// If the bomb has already exploded
        bool exploded;

        /// Construct a new Bomb component.
        ///
        /// @param pRadius @ref radius
        /// @param pExplosionDelay @ref explosionDelay
        Bomb(size_t pRadius = 1, std::chrono::milliseconds pExplosionDelay = std::chrono::milliseconds(2000))
            : placedTime(std::chrono::steady_clock::now()), radius(pRadius), explosionDelay(pExplosionDelay),
              exploded(false){};

        /// Explode the bomb.
        ///
        /// @param pos position of the bomb.
        /// @param data world data.
        void explode(const Position &pos, ecs::SystemData data);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_BOMB_HPP_ */
