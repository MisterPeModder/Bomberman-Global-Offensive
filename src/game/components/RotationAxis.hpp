#ifndef GAME_COMPONENTS_ROTATIONAXIS_HPP_
#define GAME_COMPONENTS_ROTATIONAXIS_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    namespace components
    {
        struct RotationAxis : public ecs::Component {
            raylib::core::Vector3 rotationAxis;

            RotationAxis(raylib::core::Vector3 &protationAxis) : rotationAxis(protationAxis) {}
            RotationAxis(float px, float py, float pz) : rotationAxis(px, py, pz) {}
        };
    } // namespace components
} // namespace game

#endif
