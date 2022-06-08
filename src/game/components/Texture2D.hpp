#ifndef GAME_COMPONENTS_TEXTURE2D_HPP_
#define GAME_COMPONENTS_TEXTURE2D_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game
{
    namespace components
    {
        struct Texture2D : public ecs::Component {
            raylib::model::Texture2D texture;

            Texture2D(raylib::model::Texture2D &ptexture) : texture(ptexture) {}
            Texture2D(std::filesystem::path &path) : texture(path) {}
        };
    } // namespace components
} // namespace game

#endif
