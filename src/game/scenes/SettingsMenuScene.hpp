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
            RESET,
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
            KEYBINDS_GAMEPAD_FIRST,
            WIDGET_ID_SIZE,
        };

        enum WIDGET_GAMEPAD_ID {
            KEYBINDS_GAMEPAD_BOMB,
            KEYBINDS_GAMEPAD_ACTIVABLE,
            KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE,
            KEYBINDS_GAMEPAD_NEXT_ACTIVABLE,
            KEYBINDS_GAMEPAD_COUNT
        };
        SettingsMenuScene();

        void setupWorld() override;

        static int getGamepadWidgetId(WIDGET_GAMEPAD_ID action, size_t user);

      private:
        struct Section {
            raylib::core::Vector2f pos;
            raylib::core::Vector2f size;
            raylib::core::Color color;
            localization::ResourceString name;
        };

        void loadSection(Section section, std::function<void(const Section &)> onLoad);
        void _loadKeyboardKeybinds(const Section &section);
        void _updateActionKey(GameAction action);
        void _fillGamepadButtonStrings();

        void _loadGamepadKeybinds(const Section &section);
        void _loadGamepadProfile(const Section &section, size_t id);
        void _updateActionGamepad(GameAction action, size_t id);

        std::array<components::Identity::Id, static_cast<size_t>(GameAction::COUNT)> _actionsKeyboardBindings;
        std::array<components::Identity::Id, static_cast<size_t>(GameAction::COUNT)> _actionsGamepadBindings[4];
        std::unordered_map<raylib::core::Gamepad::Button, std::string_view> _gamepadButtonStrings;
    };
} // namespace game

#endif /* !GAME_SCENES_SETTINGSMENUSCENES_HPP_ */
