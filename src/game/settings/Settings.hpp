/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Profile
*/

#ifndef GAME_PROFILE_HPP_
#define GAME_PROFILE_HPP_

#include <filesystem>
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
            class InvalidSettingsValue : public std::runtime_error {
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

            /// Get the Settings File Path.
            /// @note The path is settings/settings.cfg.
            ///
            /// @return std::filesystem::path settings file path.
            static std::filesystem::path getSettingsFilePath();

            /// Save the settings at @ref getSettingsFilePath().
            ///
            /// @throw std::runtime_error if the file can't be opened (or created).
            void save() const;

            /// Load the settings from @ref getSettingsFilePath().
            /// @note Unknown values will be ignored. Invalid values will be replaced by default ones.
            void load();

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
            /// @todo Define valid/invalid resolutions for the game and throw @ef InvalidSettingsValue for invalid
            /// resolutions.
            void setResolution(raylib::core::Vector2f resolution);

            /// Get the target resolution of the window.
            ///
            /// @return the target resolution of the window.
            raylib::core::Vector2f getResolution() const;

            /// Enable/disable the fullscreen mode.
            ///
            /// @param fullscreen whether or not the fullscreen must be enabled (true to enable).
            void setFullscreen(bool fullscreen = true);

            /// Check if the fullscreen mode is required.
            ///
            /// @retval true if the fullscreen mode is required.
            bool isFullscreen() const;

          private:
            /// Load a value from its string representation.
            ///
            /// @param key value name.
            /// @param value value data.
            void loadValue(std::string_view key, std::string_view value);

            float _sfxVolume;
            float _musicVolume;
            unsigned int _targetFramerate;
            raylib::core::Vector2f _resolution;
            bool _fullscreen;
        };
    } // namespace settings
} // namespace game

/// Output stream operator overload.
/// @note This function is used for the settings save in the file.
///
/// @param stream output stream.
/// @param settings settings to export.
/// @return std::ostream& output stream.
///
std::ostream &operator<<(std::ostream &stream, const game::settings::Settings &settings);

#endif /* !GAME_PROFILE_HPP_ */
