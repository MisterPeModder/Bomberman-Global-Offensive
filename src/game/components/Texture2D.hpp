#ifndef GAME_COMPONENTS_TEXTURE2D_HPP_
#define GAME_COMPONENTS_TEXTURE2D_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game
{
    namespace components
    {
        struct Texture2D : public ecs::Component, public raylib::model::Texture2D {
            Texture2D(raylib::model::Texture2D &ptexture) : raylib::model::Texture2D(ptexture) {}
            Texture2D(std::filesystem::path &path) : raylib::model::Texture2D(path) {}
        };
    } // namespace components
} // namespace game

#endif
