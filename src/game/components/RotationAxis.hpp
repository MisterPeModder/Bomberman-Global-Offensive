/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** RotationAxis
*/

#ifndef GAME_COMPONENTS_ROTATIONAXIS_HPP_
#define GAME_COMPONENTS_ROTATIONAXIS_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game::components
{
    struct RotationAxis : public ecs::Component, public raylib::core::Vector3f {
        RotationAxis(raylib::core::Vector3f pRotationAxis) : Vector3(pRotationAxis) {}
        RotationAxis(float px = 0, float py = 0, float pz = 0) : Vector3(px, py, pz) {}
        RotationAxis(int px = 0, int py = 0, int pz = 0) : Vector3(px, py, pz) {}
    };
} // namespace game::components

#endif
