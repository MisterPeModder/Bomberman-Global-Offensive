#ifndef GAME_COMPONENTS_COLOR_HPP_
#define GAME_COMPONENTS_COLOR_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Color.hpp"

namespace game
{
    namespace components
    {
        struct Color : public ecs::Component {
            raylib::core::Color color;

            Color(raylib::core::Color &pcolor) : color(pcolor) {}
            Color(float pr, float pg, float pb, float pa = 0) : color(pr, pg, pb, pa) {}
        };
    } // namespace components
} // namespace game

#endif
