#ifndef GAME_COMPONENTS_TEXTURE2D_HPP_
#define GAME_COMPONENTS_TEXTURE2D_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game
{
    struct Texture2D : public ecs::Component, public raylib::textures::Texture2D {
        Texture2D(raylib::textures::Texture2D &pTexture) : raylib::textures::Texture2D(pTexture) {}
        Texture2D(std::filesystem::path &pPath) : raylib::textures::Texture2D(pPath) {}
    };
} // namespace game

#endif
