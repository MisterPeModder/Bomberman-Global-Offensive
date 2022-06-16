/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Texture2D
*/

#ifndef GAME_COMPONENTS_TEXTURE2D_HPP_
#define GAME_COMPONENTS_TEXTURE2D_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::components
{
    struct Texture2D : public ecs::Component, public raylib::textures::Texture2D {
        Texture2D(const raylib::textures::Texture2D &pTexture) : raylib::textures::Texture2D(pTexture) {}
        Texture2D(const std::filesystem::path &pPath) : raylib::textures::Texture2D(pPath) {}
    };
} // namespace game::components

#endif
