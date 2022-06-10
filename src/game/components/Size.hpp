/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Size
*/

#ifndef GAME_COMPONENTS_SIZE_HPP_
#define GAME_COMPONENTS_SIZE_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    struct Size : public ecs::Component, public raylib::core::Vector3 {
        Size(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}
        Size(Vector3 vector) : Vector3(vector) {}
        Size(Vector2 vector) : Vector3(vector) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_SIZE_HPP_ */
