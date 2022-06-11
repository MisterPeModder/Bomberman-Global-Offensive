#ifndef GAME_COMPONENTS_ROTATIONAXIS_HPP_
#define GAME_COMPONENTS_ROTATIONAXIS_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    struct RotationAxis : public ecs::Component, public raylib::core::Vector3 {
        RotationAxis(raylib::core::Vector3 pRotationAxis) : raylib::core::Vector3(pRotationAxis) {}
        RotationAxis(float px, float py, float pz) : raylib::core::Vector3(px, py, pz) {}
    };
} // namespace game

#endif
