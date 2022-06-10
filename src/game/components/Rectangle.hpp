/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#include "ecs/Component.hpp"
#include "raylib/shapes/Rectangle.hpp"

#pragma once

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
