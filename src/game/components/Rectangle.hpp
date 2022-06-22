/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Rectangle
*/

#ifndef GAME_COMPONENTS_RECTANGLE_HPP_
#define GAME_COMPONENTS_RECTANGLE_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game::components
{
    struct Rectangle : public ecs::Component, public raylib::shapes::Rectangle {
        float outlineThickness;
        raylib::core::Color outlineColor;

        Rectangle() : raylib::shapes::Rectangle(), outlineThickness(0.f) {}
        Rectangle(float pOutlineThickness, raylib::core::Color pOutlineColor = raylib::core::Color::BLACK)
            : raylib::shapes::Rectangle(), outlineThickness(pOutlineThickness), outlineColor(pOutlineColor)
        {
        }
    };
} // namespace game::components

#endif
