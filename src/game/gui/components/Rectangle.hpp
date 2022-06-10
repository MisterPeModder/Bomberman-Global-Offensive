/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#ifndef RECTANGLE_COMPONENTS_
#define RECTANGLE_COMPONENTS_

#include "ecs/Component.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game
{
    struct Rectangle : public ecs::Component, public raylib::shapes::Rectangle {
        Rectangle(raylib::core::Vector2 ppos = {}, raylib::core::Vector2 psize = {1, 1},
            raylib::core::Color pcolor = raylib::core::Color::DEFAULT_COLOR)
            : raylib::shapes::Rectangle(ppos, psize, pcolor)
        {
        }
    };
} // namespace game

#endif /* RECTANGLE_COMPONENTS_ */