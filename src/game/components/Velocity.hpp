/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movable
*/

#ifndef GAME_COMPONENTS_VELOCITY_HPP_
#define GAME_COMPONENTS_VELOCITY_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game::components
{
    /// Velocity component.
    struct Velocity : public ecs::Component, public raylib::core::Vector3 {
        /// Construct a new Velocity component.
        ///
        /// @param px velocity on x axis.
        /// @param py velocity on y axis.
        /// @param pz velocity on z axis.
        Velocity(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}

        /// Construct a new Velocity component.
        ///
        /// @param vector velocity vector.
        Velocity(Vector3 vector) : Vector3(vector) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_VELOCITY_HPP_ */
