/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** MainMenuScene
*/

#ifndef GAME_SCENES_MAINMENUSCENES_HPP_
#define GAME_SCENES_MAINMENUSCENES_HPP_

#include "ecs/World.hpp"
#include "game/scenes/AScene.hpp"

namespace game
{
    class MainMenuScene : public AScene {
      public:
        enum WIDGET_ID {
            PLAY,
            SETTINGS,
            LOGOUT,
        };
        MainMenuScene();
    };
} // namespace game

#endif /* !GAME_SCENES_MAINMENUSCENES_HPP_ */
