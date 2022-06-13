#ifndef GAME_COMPONENTS_IMAGE_HPP_
#define GAME_COMPONENTS_IMAGE_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Image.hpp"

namespace game
{
    struct Image : public ecs::Component, public raylib::textures::Image {
        Image(raylib::textures::Image &pimage) : raylib::textures::Image(pimage) {}
        Image(std::filesystem::path &path) : raylib::textures::Image(path) {}
    };
} // namespace game

#endif
