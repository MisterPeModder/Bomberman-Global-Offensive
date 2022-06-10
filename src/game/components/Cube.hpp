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
    struct Cube : public ecs::Component, public raylib::shapes::Cube {
        Cube(const raylib::core::Vector2 &ppos = {}, const raylib::core::Vector2 &psize = {1, 1},
            const raylib::core::Color &pcolor = raylib::core::Color::DEFAULT_COLOR)
            : raylib::shapes::Cube(ppos, psize, pcolor)
        {
        }
    };
} // namespace game::components

#endif
