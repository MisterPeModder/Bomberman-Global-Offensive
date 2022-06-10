/*
** EPITECH PROJECT, 2022
** Bomberman
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
    struct Cube : public ecs::Component {
        /// Stored cube.
        raylib::shapes::Cube cube;

        /// Create a default cube component.
        Cube() : cube() {}

        /// Construct a new Cube component with parameters.
        ///
        /// @param position position.
        /// @param size size.
        /// @param color color.
        Cube(raylib::core::Vector3 position, raylib::core::Vector3 size, Color color) : cube(position, size, color) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_CUBE_HPP_ */
