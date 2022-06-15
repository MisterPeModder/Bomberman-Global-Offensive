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
        Vector3 rotationAxis;

        RotationAxis(Vector3 pRotationAxis) : rotationAxis(pRotationAxis) {}
        RotationAxis(float px = 0, float py = 0, float pz = 0) : rotationAxis(Vector3{px, py, pz}) {}
        RotationAxis(int px = 0, int py = 0, int pz = 0) : rotationAxis(Vector3{static_cast<float>(px), static_cast<float>(py), static_cast<float>(pz)}) {}
    };
} // namespace game::components

#endif
