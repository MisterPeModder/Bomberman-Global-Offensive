#ifndef GAME_COMPONENTS_POSITION_HPP_
#define GAME_COMPONENTS_POSITION_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    namespace components
    {
        struct Position : public ecs::Component, public raylib::core::Vector3 {
            Position(raylib::core::Vector2 &pposition) : raylib::core::Vector3(pposition) {}
            Position(raylib::core::Vector3 &pposition) : raylib::core::Vector3(pposition) {}
            Position(float px, float py, float pz = 0) : raylib::core::Vector3(px, py, pz) {}
        };
    } // namespace components
} // namespace game

#endif
