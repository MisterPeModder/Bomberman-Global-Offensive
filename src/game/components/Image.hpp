/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Image
*/

#ifndef GAME_COMPONENTS_IMAGE_HPP_
#define GAME_COMPONENTS_IMAGE_HPP_

#include <filesystem>
#include "ecs/Component.hpp"
#include "raylib/textures/Image.hpp"

namespace game::components
{
    struct Image : public ecs::Component, public raylib::textures::Image {
        Image(const raylib::textures::Image &pimage) : raylib::textures::Image(pimage) {}
        Image(const std::filesystem::path &path) : raylib::textures::Image(path) {}
    };
} // namespace game::components

#endif
