/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Position2D
*/

#ifndef GAME_COMPONENTS_POSITION2D_HPP_
#define GAME_COMPONENTS_POSITION2D_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    struct Position2D : public ecs::Component, public raylib::core::Vector2f {
        Position2D(float px = 0, float py = 0) : Vector2(px, py) {}
        Position2D(int px = 0, int py = 0) : Vector2(px, py) {}
        Position2D(Vector2 vector) : Vector2(vector) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_POSITION2D_HPP_ */
