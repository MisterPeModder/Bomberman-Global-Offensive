/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Cube
*/

#ifndef GAME_COMPONENTS_CUBE_HPP_
#define GAME_COMPONENTS_CUBE_HPP_

#include "ecs/Component.hpp"
#include "raylib/shapes/Cube.hpp"

namespace game::components
{
    /// Cube component
    struct Cube : public ecs::Component, public raylib::shapes::Cube {
        /// Create a default cube component.
        Cube() : raylib::shapes::Cube() {}

        /// Construct a new Cube component with parameters.
        ///
        /// @param position position.
        /// @param size size.
        /// @param color color.
        Cube(raylib::core::Vector3f position, raylib::core::Vector3f size, Color color)
            : raylib::shapes::Cube(position, size, color)
        {
        }
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_CUBE_HPP_ */
