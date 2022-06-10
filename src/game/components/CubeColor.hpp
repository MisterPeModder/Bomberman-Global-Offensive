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

namespace game
{
    struct CubeColor : public ecs::Component, public raylib::core::Color {
        CubeColor(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
            : raylib::core::Color(cr, cg, cb, ca)
        {
        }
        CubeColor(const raylib::core::Color &other) : raylib::core::Color(other) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_CUBECOLOR_HPP_ */
