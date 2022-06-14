/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Worlds
*/

#ifndef GAME_WORLDS_WORLDS_HPP_
#define GAME_WORLDS_WORLDS_HPP_

#include "game/Game.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class Worlds {
      public:
        static void loadGameWorld(game::Game &game);
        static void loadSplashWorld(ecs::World &world);
        static void loadMainWorld(ecs::World &world);
        static void loadSettingsWorld(ecs::World &world);
        static void loadTestWorld(ecs::World &world);
    };
} // namespace game

#endif /* !WORLDS_HPP_ */
