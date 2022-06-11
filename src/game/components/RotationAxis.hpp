#ifndef GAME_COMPONENTS_ROTATIONAXIS_HPP_
#define GAME_COMPONENTS_ROTATIONAXIS_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game::components
{
    struct RotationAxis : public ecs::Component, public raylib::core::Vector3f {
        RotationAxis(raylib::core::Vector3f pRotationAxis) : raylib::core::Vector3f(pRotationAxis) {}
        RotationAxis(float px, float py, float pz) : raylib::core::Vector3f(px, py, pz) {}
        RotationAxis(int px, int py, int pz) : raylib::core::Vector3f(px, py, pz) {}
    };
} // namespace game::components

#endif
