#ifndef GAME_COMPONENTS_ANIMATION_HPP_
#define GAME_COMPONENTS_ANIMATION_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/model/Animation.hpp"

namespace game::components
{
    struct Animation : public ecs::Component, public raylib::model::Animation {
        Animation(const raylib::model::Animation &panimation) : raylib::model::Animation(panimation) {}
        Animation(const std::filesystem::path &path) : raylib::model::Animation(path) {}
    };
} // namespace game::components

#endif
