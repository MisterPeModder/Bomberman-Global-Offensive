/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Position
*/

#ifndef GAME_COMPONENTS_POSITION_HPP_
#define GAME_COMPONENTS_POSITION_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    struct Position : public ecs::Component, public raylib::core::Vector3 {
        Position(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}
        Position(Vector3 vector) : Vector3(vector) {}
        Position(Vector2 vector) : Vector3(vector) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_POSITION_HPP_ */
