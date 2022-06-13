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
#include "raylib/images/Image.hpp"

namespace game::components
{
    struct Image : public ecs::Component, public raylib::model::Image {
        Image(const raylib::model::Image &pimage) : raylib::model::Image(pimage) {}
        Image(const std::filesystem::path &path) : raylib::model::Image(path) {}
    };
} // namespace game::components

#endif
