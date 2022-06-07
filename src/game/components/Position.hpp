#ifndef GAME_COMPONENTS_POSITION_HPP_
#define GAME_COMPONENTS_POSITION_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    namespace components
    {
        struct Position : public ecs::Component {
            raylib::core::Vector3 position;

            Position(raylib::core::Vector3 &pposition) : position(pposition) {}
            Position(float px, float py, float pz = 0) : position(px, py, pz) {}
        };
    } // namespace components
} // namespace game

#endif
