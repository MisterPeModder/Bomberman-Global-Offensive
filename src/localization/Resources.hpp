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
        /// Simple hello world.
        constexpr ResourceString rsHello("Hello, World!");
        constexpr ResourceString rsSettings("Settings");
        namespace settings
        {
            constexpr ResourceString rsSettingsGraphic("Graphic");
            constexpr ResourceString rsSettingsAudio("Audio");
            constexpr ResourceString rsSettingsKeybinds("Keybinds");

        } // namespace settings
    }     // namespace resources
} // namespace localization

#endif /* !LOCALIZATION_RESOURCES_HPP_ */
