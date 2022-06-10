/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** CubeColor
*/

#ifndef GAME_COMPONENTS_CUBECOLOR_HPP_
#define GAME_COMPONENTS_CUBECOLOR_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Color.hpp"

namespace game::components
{
    /// Cube color component
    struct CubeColor : public ecs::Component, public raylib::core::Color {
        /// Construct a new Cube Color component.
        ///
        /// @param cr red component.
        /// @param cg green component.
        /// @param cb blue component.
        /// @param ca alpha component.
        CubeColor(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
            : raylib::core::Color(cr, cg, cb, ca)
        {
        }

        /// Construct a new Cube Color component
        ///
        /// @param color color.
        CubeColor(const raylib::core::Color &color) : raylib::core::Color(color) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_CUBECOLOR_HPP_ */
