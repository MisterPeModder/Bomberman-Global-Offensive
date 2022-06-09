#ifndef GAME_COMPONENTS_SCALE_HPP_
#define GAME_COMPONENTS_SCALE_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    namespace components
    {
        struct Scale : public ecs::Component, public raylib::core::Vector3 {
            Scale(raylib::core::Vector3 &pscale) : raylib::core::Vector3(pscale) {}
            Scale(float px, float py, float pz = 1) : raylib::core::Vector3(px, py, pz) {}
        };
    } // namespace components
} // namespace game

#endif
