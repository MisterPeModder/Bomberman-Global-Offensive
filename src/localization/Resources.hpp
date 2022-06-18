/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Resources
*/

#ifndef LOCALIZATION_RESOURCES_HPP_
#define LOCALIZATION_RESOURCES_HPP_

#include "ResourceString.hpp"

namespace localization
{
    /// used to register all project string resources as const @ref ResourceString.
    namespace resources
    {
        constexpr ResourceString rsTitle("Bomberman: Global Offensive");
        constexpr ResourceString rsShortTitle("BM:GO");

        constexpr ResourceString rsBack("Back");

        constexpr ResourceString rsUser1("User 1");
        constexpr ResourceString rsUser2("User 2");
        constexpr ResourceString rsUser3("User 3");
        constexpr ResourceString rsUser4("User 4");

        constexpr ResourceString rsSettings("SETTINGS");

        namespace keybinds
        {
            constexpr ResourceString rsKeyBindLeft("Left");
            constexpr ResourceString rsKeyBindRight("Right");
            constexpr ResourceString rsKeyBindUp("Up");
            constexpr ResourceString rsKeyBindDown("Down");
            constexpr ResourceString rsKeyBindBomb("Bomb");
            constexpr ResourceString rsKeyBindActivable("Activable");
            constexpr ResourceString rsKeyBindActivableLeft("Activable Left");
            constexpr ResourceString rsKeyBindActivableRight("Activable Right");
            constexpr ResourceString rsKeyBindActivableShort("Activ.");
            constexpr ResourceString rsKeyBindActivableLeftShort("L Activ.");
            constexpr ResourceString rsKeyBindActivableRightShort("R Activ.");
        } // namespace keybinds

        namespace languages
        {
            constexpr ResourceString rsLanguageEnglish("English");
            constexpr ResourceString rsLanguageFrench("Français");
        } // namespace languages

        namespace settings
        {
            constexpr ResourceString rsSettingsGraphics("Graphics");
            constexpr ResourceString rsSettingsFullscreen("Fullscreen");
            constexpr ResourceString rsSettingsResolution("Resolution");
            constexpr ResourceString rsSettingsFPS("FPS");

            constexpr ResourceString rsSettingsLanguage("Language");

            constexpr ResourceString rsSettingsAudio("Audio");
            constexpr ResourceString rsSettingsMuteUnmute("Mute/Unmute");
            constexpr ResourceString rsSettingsMusic("Music");
            constexpr ResourceString rsSettingsSfx("Sfx");

            constexpr ResourceString rsSettingsKeybinds("Keybinds");
            constexpr ResourceString rsSettingsControllerKeybinds("(Controller)");
            constexpr ResourceString rsSettingsKeyboardKeybinds("(Keyboard)");

        } // namespace settings
        namespace menu
        {
            constexpr ResourceString rsMenuSettings("Settings");
            constexpr ResourceString rsMenuPlay("Play");
            constexpr ResourceString rsMenuQuit("Quit");
            constexpr ResourceString rsNotConnected("Not connected");
            constexpr ResourceString rsConnected("Connected");
        } // namespace menu
    }     // namespace resources
} // namespace localization

#endif /* !LOCALIZATION_RESOURCES_HPP_ */
