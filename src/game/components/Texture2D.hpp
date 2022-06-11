#ifndef GAME_COMPONENTS_TEXTURE2D_HPP_
#define GAME_COMPONENTS_TEXTURE2D_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::components
{
    struct Texture2D : public ecs::Component, public raylib::model::Texture2D {
        Texture2D(const raylib::model::Texture2D &pTexture) : raylib::model::Texture2D(pTexture) {}
        Texture2D(const std::filesystem::path &pPath) : raylib::model::Texture2D(pPath) {}
    };
} // namespace game::components

#endif
