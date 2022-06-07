#ifndef GAME_COMPONENTS_ANIMATION_HPP_
#define GAME_COMPONENTS_ANIMATION_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Animation.hpp"

namespace game
{
    namespace components
    {
        struct Animation : public ecs::Component {
            raylib::model::Animation animation;

            Animation(raylib::model::Animation &panimation) : animation(panimation) {}
            Animation(std::filesystem::path &path) : animation(path) {}
        };
    } // namespace components
} // namespace game

#endif
