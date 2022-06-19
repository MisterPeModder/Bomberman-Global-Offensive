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
        constexpr ResourceString rsBack("Back");

        constexpr ResourceString rsSettings("SETTINGS");

        namespace settings
        {
            constexpr ResourceString rsSettingsGraphics("Graphics");
            constexpr ResourceString rsSettingsFullscreen("Fullscreen");
            constexpr ResourceString rsSettingsResolution("Resolution");

            constexpr ResourceString rsSettingsAudio("Audio");
            constexpr ResourceString rsSettingsMute("Mute");
            constexpr ResourceString rsSettingsVolume("Volume");

            constexpr ResourceString rsSettingsKeybinds("Keybinds");

        } // namespace settings
        namespace menu
        {
            constexpr ResourceString rsMenuSettings("Settings");
            constexpr ResourceString rsMenuPlay("Play");
            constexpr ResourceString rsMenuQuit("Quit");
        } // namespace menu
        namespace hud
        {
            constexpr ResourceString rsNumberbomb("Number Bomb");
            constexpr ResourceString rsSpeed("Speed");
            constexpr ResourceString rsPowerBomb("Power Bomb");
            constexpr ResourceString rsTest("");
            // constexpr ResourceString rs();
        } // namespace hud

    } // namespace resources
} // namespace localization

#endif /* !LOCALIZATION_RESOURCES_HPP_ */
