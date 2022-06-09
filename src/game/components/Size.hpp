#ifndef GAME_COMPONENTS_SIZE_HPP_
#define GAME_COMPONENTS_SIZE_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game
{
    namespace components
    {
        struct Size : public ecs::Component, public raylib::core::Vector3 {
            Size(raylib::core::Vector2 &psize) : raylib::core::Vector3(psize) {}
            Size(raylib::core::Vector3 &psize) : raylib::core::Vector3(psize) {}
            Size(float px, float py, float pz = 1) : raylib::core::Vector3(px, py, pz) {}
        };
    } // namespace components
} // namespace game

#endif
