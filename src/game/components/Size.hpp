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

namespace game::components
{
    struct Size : public ecs::Component, public raylib::core::Vector3f {
        Size(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}
        Size(int px = 0, int py = 0, int pz = 0) : Vector3(px, py, pz) {}
        Size(raylib::core::Vector3f vector) : raylib::core::Vector3f(vector) {}
        Size(raylib::core::Vector2f vector) : raylib::core::Vector3f(vector) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_SIZE_HPP_ */
