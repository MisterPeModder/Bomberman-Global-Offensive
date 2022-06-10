/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movable
*/

#ifndef GAME_COMPONENTS_MOVABLE_HPP_
#define GAME_COMPONENTS_MOVABLE_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    struct Movable : public ecs::Component, public raylib::core::Vector2 {
        Movable(float px = 0, float py = 0) : Vector2(px, py) {}
        Movable(Vector2 vector) : Vector2(vector) {}
        Movable(Vector2 vector) : Vector2(vector) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_MOVABLE_HPP_ */
