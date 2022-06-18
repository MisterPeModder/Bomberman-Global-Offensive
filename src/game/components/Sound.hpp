/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Sound
*/

#ifndef GAME_COMPONENTS_SOUND_HPP_
#define GAME_COMPONENTS_SOUND_HPP_

#include "ecs/Component.hpp"
#include "raylib/core/Sound.hpp"

namespace game::components
{
    struct Sound : public ecs::Component, public raylib::core::Sound {
        Sound(const raylib::core::Sound &pSound) : raylib::core::Sound(pSound) {}
        Sound(const std::filesystem::path &path) : raylib::core::Sound(path) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_SOUND_HPP_ */
