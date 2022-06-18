/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsMenuScene
*/

#ifndef GAME_SCENES_SETTINGSMENUSCENES_HPP_
#define GAME_SCENES_SETTINGSMENUSCENES_HPP_

#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "game/scenes/AScene.hpp"

namespace game
{
    class SettingsMenuScene : public AScene {
      public:
        enum WIDGET_ID {
            BACK,
            VOLUME_MUTE,
            MUSIC_VOLUME_0,
            MUSIC_VOLUME_33,
            MUSIC_VOLUME_66,
            MUSIC_VOLUME_100,
            SFX_VOLUME_0,
            SFX_VOLUME_33,
            SFX_VOLUME_66,
            SFX_VOLUME_100,
            FULLSCREEN,
            RES_1,
            RES_2,
            RES_3,
            WIDGET_ID_SIZE,
        };
        SettingsMenuScene();
    };
} // namespace game

#endif /* !GAME_SCENES_SETTINGSMENUSCENES_HPP_ */
