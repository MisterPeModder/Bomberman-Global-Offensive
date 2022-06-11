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
    struct Size : public ecs::Component, public raylib::core::Vector3f {
        Size(float px = 1, float py = 1, float pz = 1) : Vector3(px, py, pz) {}
        Size(Vector3f vector) : Vector3(vector) {}
        Size(Vector2f vector) : Vector3(vector) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_SIZE_HPP_ */
