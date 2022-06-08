#ifndef GAME_COMPONENTS_IMAGE_HPP_
#define GAME_COMPONENTS_IMAGE_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/images/Image.hpp"

namespace game
{
    namespace components
    {
        struct Image : public ecs::Component {
            raylib::model::Image image;

            Image(raylib::model::Image &pimage) : image(pimage) {}
            Image(std::filesystem::path &path) : image(path) {}
        };
    } // namespace components
} // namespace game

#endif
