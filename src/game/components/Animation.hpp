#ifndef GAME_COMPONENTS_ANIMATION_HPP_
#define GAME_COMPONENTS_ANIMATION_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Animation.hpp"

namespace game
{
    namespace components
    {
        struct Animation : public ecs::Component, public raylib::model::Animation {
            Animation(raylib::model::Animation &panimation) : raylib::model::Animation(panimation) {}
            Animation(std::filesystem::path &path) : raylib::model::Animation(path) {}
        };
    } // namespace components
} // namespace game

#endif
