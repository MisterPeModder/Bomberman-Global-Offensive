/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Worlds
*/

#ifndef GAME_WORLDS_HPP_
#define GAME_WORLDS_HPP_

#include "ecs/World.hpp"

namespace game
{
    class Worlds {
      public:
        // enum WORLDS_TYPE {
        //     TEST_WORLD,
        //     SPLASH_SCREEN,
        //     MAIN_MENU,
        //     SETTINGS_MENU,
        //     GAME,
        //     PAUSE,

        //     WORLDS_TYPE_SIZE,
        // };
        // static void join(ecs::World &world, WORLDS_TYPE type);
        // static void leave(ecs::World &world, WORLDS_TYPE type);
        // static void clear(ecs::World &world);

        // private:
        static void loadSplashWorld(ecs::World &world);
        static void loadMainWorld(ecs::World &world);
        static void loadSettingsWorld(ecs::World &world);
        static void loadTestWorld(ecs::World &world);
        // static void loadGameWorld(ecs::World &world, map::Map &map, game::Game::Parameters &params);
        // static bool worldsJoined[WORLDS_TYPE_SIZE];
    };
} // namespace game

#endif /* !GAME_WORLDS_HPP_ */
