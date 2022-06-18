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

        constexpr ResourceString rsSettings("SETTINGS");

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
            constexpr ResourceString rsSettingsLanguage("Language");

            constexpr ResourceString rsSettingsAudio("Audio");
            constexpr ResourceString rsSettingsMuteUnmute("Mute/Unmute");
            constexpr ResourceString rsSettingsMusic("Music");
            constexpr ResourceString rsSettingsSfx("Sfx");

            constexpr ResourceString rsSettingsKeybinds("Keybinds");

        } // namespace settings
        namespace menu
        {
            constexpr ResourceString rsMenuSettings("Settings");
            constexpr ResourceString rsMenuPlay("Play");
            constexpr ResourceString rsMenuQuit("Quit");
        } // namespace menu
    }     // namespace resources
} // namespace localization

#endif /* !LOCALIZATION_RESOURCES_HPP_ */
