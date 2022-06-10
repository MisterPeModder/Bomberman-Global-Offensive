#ifndef GAME_COMPONENTS_IMAGE_HPP_
#define GAME_COMPONENTS_IMAGE_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/images/Image.hpp"

namespace game
{
    struct Image : public ecs::Component, public raylib::model::Image {
        Image(raylib::model::Image &pimage) : raylib::model::Image(pimage) {}
        Image(std::filesystem::path &path) : raylib::model::Image(path) {}
    };
} // namespace game

#endif
