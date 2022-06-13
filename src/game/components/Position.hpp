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

namespace game::components
{
    struct Position : public ecs::Component, public raylib::core::Vector3f {
        Position(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}
        Position(int px = 0, int py = 0, int pz = 0) : Vector3(px, py, pz) {}
        Position(raylib::core::Vector3f vector) : raylib::core::Vector3f(vector) {}
        Position(raylib::core::Vector2f vector) : raylib::core::Vector3f(vector) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_POSITION_HPP_ */
