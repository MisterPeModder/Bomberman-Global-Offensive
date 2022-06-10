#ifndef GAME_COMPONENTS_ROTATIONAXIS_HPP_
#define GAME_COMPONENTS_ROTATIONAXIS_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game::components
{
    struct RotationAxis : public ecs::Component, public raylib::core::Vector3 {
        RotationAxis(const raylib::core::Vector3 &protationAxis) : raylib::core::Vector3(protationAxis) {}
        RotationAxis(float px, float py, float pz) : raylib::core::Vector3(px, py, pz) {}
        RotationAxis(int px, int py, int pz) : raylib::core::Vector3(px, py, pz) {}
    };
} // namespace game::components

#endif
