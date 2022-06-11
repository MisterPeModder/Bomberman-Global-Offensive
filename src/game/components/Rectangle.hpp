/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#ifndef GAME_COMPONENTS_RECTANGLE_HPP_
#define GAME_COMPONENTS_RECTANGLE_HPP_

#include "ecs/Component.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game::components
{
    struct Rectangle : public ecs::Component, public raylib::shapes::Rectangle {
        Rectangle(const raylib::core::Vector2 &ppos = {}, const raylib::core::Vector2 &psize = {1, 1},
            const raylib::core::Color &pcolor = raylib::core::Color::DEFAULT_COLOR)
            : raylib::shapes::Rectangle(ppos, psize, pcolor)
        {
        }
    };
} // namespace game::components

#endif
