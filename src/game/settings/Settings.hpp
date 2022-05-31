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
        class Settings {
          public:
            class InvalidSettingsValue : public std::logic_error {
              public:
                InvalidSettingsValue(std::string_view message);
            };

            Settings();
            Settings(const Settings &other) = default;
            ~Settings() = default;

            Settings &operator=(const Settings &other) = default;

            void setSfxVolume(float volume);
            float getSfxVolume() const;

            void setMusicVolume(float volume);
            float getMusicVolume() const;

            void setTargetFramerate(unsigned int target);
            unsigned int getTargetFramerate() const;

            void setResolution(raylib::core::Vector2 resolution);
            raylib::core::Vector2 getResolution() const;

            void setFullscreen(bool fullscreen = true);
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
