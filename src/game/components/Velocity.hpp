/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movable
*/

#ifndef GAME_COMPONENTS_VELOCITY_HPP_
#define GAME_COMPONENTS_VELOCITY_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    struct Velocity : public ecs::Component, public raylib::core::Vector3 {
        Velocity(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}
        Velocity(Vector3 vector) : Vector3(vector) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_VELOCITY_HPP_ */
