/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Background
*/

#ifndef GAME_COMPONENTS_BACKGROUND_HPP_
#define GAME_COMPONENTS_BACKGROUND_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Texture2D.hpp"

namespace game::components
{
    struct Background : public ecs::Component, public raylib::textures::Texture2D {
        Background(const raylib::textures::Texture2D &pTexture) : raylib::textures::Texture2D(pTexture) {}
        Background(const std::filesystem::path &pPath) : raylib::textures::Texture2D(pPath) {}
    };
} // namespace game::components

#endif
