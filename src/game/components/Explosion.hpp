/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Explosion
*/

#ifndef GAME_COMPONENTS_EXPLOSION_HPP_
#define GAME_COMPONENTS_EXPLOSION_HPP_

#include <chrono>
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    /// Explosion component
    struct Explosion : public ecs::Component {
        std::chrono::steady_clock::time_point placedTime;
        constexpr static std::chrono::milliseconds EXPLOSION_DURATION = std::chrono::milliseconds(400);

        /// Construct a new Explosion component.
        Explosion() : placedTime(std::chrono::steady_clock::now()){};

        /// Place an explosion at a given cell.
        ///
        /// @param data world data.
        /// @param cell explosion cell.
        static void placeExplosion(ecs::SystemData data, raylib::core::Vector2u cell);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_EXPLOSION_HPP_ */
