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
        Rectangle() : raylib::shapes::Rectangle() {}
    };
} // namespace game::components

#endif
