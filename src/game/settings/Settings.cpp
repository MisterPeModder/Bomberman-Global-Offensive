/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Settings
*/

#include "Settings.hpp"

namespace game
{
    namespace settings
    {
        Settings::InvalidSettingsValue::InvalidSettingsValue(std::string_view message)
            : std::logic_error(message.data())
        {
        }

        Settings::Settings()
            : _sfxVolume(100), _musicVolume(100), _targetFramerate(60), _resolution(1280, 720), _fullscreen(false)
        {
        }

        void Settings::setSfxVolume(float volume)
        {
            if (volume < 0 || volume > 100)
                throw InvalidSettingsValue("Volumes must be between 0 and 100.");
            _sfxVolume = volume;
        }

        float Settings::getSfxVolume() const { return _sfxVolume; }

        void Settings::setMusicVolume(float volume)
        {
            if (volume < 0 || volume > 100)
                throw InvalidSettingsValue("Volumes must be between 0 and 100.");
            _musicVolume = volume;
        }

        float Settings::getMusicVolume() const { return _musicVolume; }

        void Settings::setTargetFramerate(unsigned int target) { _targetFramerate = target; }

        unsigned int Settings::getTargetFramerate() const { return _targetFramerate; }

        void Settings::setResolution(raylib::core::Vector2 resolution) { _resolution = resolution; }

        raylib::core::Vector2 Settings::getResolution() const { return _resolution; }

        void Settings::setFullscreen(bool fullscreen) { _fullscreen = fullscreen; }

        bool Settings::isFullscreen() const { return _fullscreen; }
    } // namespace settings
} // namespace game