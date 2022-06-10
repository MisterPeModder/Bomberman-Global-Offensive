#ifndef GAME_COMPONENTS_COLOR_HPP_
#define GAME_COMPONENTS_COLOR_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Color.hpp"

namespace game
{
    struct Color : public ecs::Component, public raylib::core::Color {
        Color(const raylib::core::Color &pcolor) : raylib::core::Color(pcolor) {}
        Color(float pr, float pg, float pb, float pa = 0) : raylib::core::Color(pr, pg, pb, pa) {}
    };
} // namespace game

#endif
