/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Size2D
*/

#ifndef GAME_COMPONENTS_SIZE2D_HPP_
#define GAME_COMPONENTS_SIZE2D_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    struct Size2D : public ecs::Component, public raylib::core::Vector2f {
        Size2D(float px = 0, float py = 0) : Vector2(px, py) {}
        Size2D(int px = 0, int py = 0) : Vector2(px, py) {}
        Size2D(Vector2 vector) : Vector2(vector) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_SIZE2D_HPP_ */
