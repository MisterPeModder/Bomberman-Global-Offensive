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
    struct Size : public ecs::Component, public raylib::core::Vector3 {
        Size(const raylib::core::Vector2 &psize) : raylib::core::Vector3(psize) {}
        Size(const raylib::core::Vector3 &psize) : raylib::core::Vector3(psize) {}
        Size(float px = 1, float py = 1, float pz = 1) : raylib::core::Vector3(px, py, pz) {}
        Size(int px = 1, int py = 1, int pz = 1) : raylib::core::Vector3(px, py, pz) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_SIZE_HPP_ */
