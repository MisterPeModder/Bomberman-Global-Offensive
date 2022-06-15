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
            VOLUME_25,
            VOLUME_50,
            VOLUME_75,
            VOLUME_100,
            FULLSCREEN,
            RES_1,
            RES_2,
            RES_3,
            WIDGET_ID_SIZE,
        };
        SettingsMenuScene();

      private:
        enum CURRENT_SETTINGS_MENU { GRAPHICS, AUDIO, KEYBINDS, CURRENT_SETTINGS_MENU_SIZE };
        CURRENT_SETTINGS_MENU _currentSettingsMenu;
        // ecs::SystemTag _graphicSettings;
        // ecs::SystemTag _audioSettings;
        // ecs::SystemTag _keybindSettings;
    };
} // namespace game

#endif /* !GAME_SCENES_SETTINGSMENUSCENES_HPP_ */
