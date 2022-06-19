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
#include "game/User.hpp"
#include "game/components/Identity.hpp"
#include "game/scenes/AScene.hpp"
#include "localization/ResourceString.hpp"

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
            FPS_30,
            FPS_60,
            FPS_144,
            FPS_240,
            LANGUAGE_ENGLISH,
            LANGUAGE_FRENCH,
            KEYBINDS_KEYBOARD_UP,
            KEYBINDS_KEYBOARD_DOWN,
            KEYBINDS_KEYBOARD_LEFT,
            KEYBINDS_KEYBOARD_RIGHT,
            KEYBINDS_KEYBOARD_BOMB,
            KEYBINDS_KEYBOARD_ACTIVABLE,
            KEYBINDS_KEYBOARD_ACTIVABLE_PREVIOUS,
            KEYBINDS_KEYBOARD_ACTIVABLE_NEXT,
            WIDGET_ID_SIZE,
        };
        SettingsMenuScene();

      private:
        struct Section {
            raylib::core::Vector2f pos;
            raylib::core::Vector2f size;
            raylib::core::Color color;
            localization::ResourceString name;
        };

        void loadSection(Section section, std::function<void(const Section &)> onLoad);
        void _loadKeyboardKeybinds(const Section &section);

        std::array<components::Identity::Id, static_cast<size_t>(GameAction::COUNT)> _actionsKeyboardBindings;
    };
} // namespace game

#endif /* !GAME_SCENES_SETTINGSMENUSCENES_HPP_ */
