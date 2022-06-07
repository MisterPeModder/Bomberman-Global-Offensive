#ifndef GAME_COMPONENTS_SCALE_HPP_
#define GAME_COMPONENTS_SCALE_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    namespace components
    {
        struct Scale : public ecs::Component {
            raylib::core::Vector3 scale;

            Scale(raylib::core::Vector3 &pscale) : scale(pscale) {}
            Scale(float px, float py, float pz = 0) : scale(px, py, pz) {}
        };
    } // namespace components
} // namespace game

#endif
