/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Settings
*/

#include "Settings.hpp"
#include <filesystem>
#include <fstream>
#include "util/util.hpp"

namespace game
{
    namespace settings
    {
        Settings::InvalidSettingsValue::InvalidSettingsValue(std::string_view message)
            : std::logic_error(message.data())
        {
        }

        Settings::Settings() { loadDefaults(); }

        void Settings::loadDefaults()
        {
            _sfxVolume = 100;
            _musicVolume = 100;
            _targetFramerate = 60;
            _resolution = {1280, 720};
            _fullscreen = false;
        }

        void Settings::save() const
        {
            std::filesystem::path path = util::makePath("settings", "settings.cfg");
            std::ofstream file;

            if (!std::filesystem::is_directory("settings") || !std::filesystem::exists("settings"))
                std::filesystem::create_directory("settings");
            file.open(path, std::ios_base::out);
            if (!file.is_open())
                throw std::runtime_error("Unable to save the settings file '" + path.generic_string() + "'");
            file << "# Bomberman settings" << std::endl << std::endl;
            file << "sfx_volume=" << _sfxVolume << std::endl;
            file << "music_volume=" << _musicVolume << std::endl;
            file << "target_framerate=" << _targetFramerate << std::endl;
            file << "resolution=" << _resolution.x << "x" << _resolution.y << std::endl;
            file << "fullscreen=" << _fullscreen << std::endl;
            file.close();
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