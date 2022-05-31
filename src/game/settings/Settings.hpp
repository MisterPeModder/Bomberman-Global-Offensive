/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Profile
*/

#ifndef GAME_PROFILE_HPP_
#define GAME_PROFILE_HPP_

#include <stdexcept>
#include <string>
#include "raylib/core/Vector2.hpp"
#include <string_view>

namespace game
{
    namespace settings
    {
        /// Settings common to the game
        class Settings {
          public:
            /// Exception for invalid values in settings.
            class InvalidSettingsValue : public std::logic_error {
              public:
                /// Construct a new Invalid Settings Value exception.
                ///
                /// @param message message of the exception.
                InvalidSettingsValue(std::string_view message);
            };

            /// Construct a new Settings object.
            Settings();

            /// Construct a copy of a Settings object.
            ///
            /// @param other settings to copy.
            Settings(const Settings &other) = default;

            /// Destroys the settings.
            ~Settings() = default;

            /// Copy a Settings object in the current one.
            ///
            /// @param other settings to copy.
            /// @return Settings& @b this.
            ///
            Settings &operator=(const Settings &other) = default;

            /// Reset the settings with the default values.
            void loadDefaults();

            /// Save the settings in the file "settings/settings.cfg"
            /// @throw std::runtime_error if the file can't be opened (or created).
            void save() const;

            /// Set the sound effects Volume
            ///
            /// @param volume new volume to set ([0-100]).
            /// @throw InvalidSettingsValue when the new volume isn't in the required range.
            void setSfxVolume(float volume);

            /// Get the sound effects volume.
            ///
            /// @return the sound effects volume.
            float getSfxVolume() const;

            /// Set the music volume.
            ///
            /// @param volume new volume to set ([0-100]).
            /// @throw InvalidSettingsValue when the new volume isn't in the required range.
            void setMusicVolume(float volume);

            /// Get the music volume.
            ///
            /// @return the music volume.
            float getMusicVolume() const;

            /// Set the target framerate (frame per seconds).
            ///
            /// @param targetFPS target framerate.
            void setTargetFramerate(unsigned int targetFPS);

            /// Get the target framerate.
            ///
            /// @return the target framerate.
            unsigned int getTargetFramerate() const;

            /// Set the new resolution of the window.
            ///
            /// @param resolution new resolution.
            void setResolution(raylib::core::Vector2 resolution);

            /// Get the target resolution of the window.
            ///
            /// @return the target resolution of the window.
            raylib::core::Vector2 getResolution() const;

            /// Enable/disable the fullscreen mode.
            ///
            /// @param fullscreen whether or not the fullscreen must be enabled (true to enable).
            void setFullscreen(bool fullscreen = true);

            /// Check if the fullscreen mode is required.
            ///
            /// @retval true if the fullscreen mode is required.
            bool isFullscreen() const;

          private:
            float _sfxVolume;
            float _musicVolume;
            unsigned int _targetFramerate;
            raylib::core::Vector2 _resolution;
            bool _fullscreen;
        };
    } // namespace settings
} // namespace game

#endif /* !GAME_PROFILE_HPP_ */
