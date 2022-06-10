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

namespace game
{
    struct Cube : public ecs::Component, public raylib::shapes::Cube {
        Cube(raylib::core::Vector2 ppos = {}, raylib::core::Vector2 psize = {1, 1},
            raylib::core::Color pcolor = raylib::core::Color::DEFAULT_COLOR)
            : raylib::shapes::Cube(ppos, psize, pcolor)
        {
        }
    };
} // namespace game

#endif
