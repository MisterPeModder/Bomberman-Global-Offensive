/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Settings
*/

#include "Settings.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include "logger/Logger.hpp"
#include "util/util.hpp"

namespace game
{
    namespace settings
    {
        Settings::InvalidSettingsValue::InvalidSettingsValue(std::string_view message)
            : std::runtime_error(message.data())
        {
        }

        Settings::Settings() { loadDefaults(); }

        void Settings::loadDefaults()
        {
            _sfxVolume = 100;
            _musicVolume = 100;
            _masterVolume = 100;
            _targetFramerate = 60;
            _resolution = {1280, 720};
            _fullscreen = false;
            _locale = "en";
        }

        std::filesystem::path Settings::getSettingsFilePath() { return util::makePath("settings", "settings.cfg"); }

        void Settings::save() const
        {
            std::filesystem::path path = getSettingsFilePath();
            std::ofstream file;

            std::filesystem::create_directory("settings");
            file.open(path, std::ios_base::out);
            if (!file.is_open())
                throw std::runtime_error("Unable to save the settings file '" + path.generic_string() + "'");
            file << *this;
            file.close();
        }

        void Settings::loadValue(std::string_view key, std::string_view value)
        {
            if (key == "sfx_volume")
                setSfxVolume(std::stof(value.data()));
            else if (key == "music_volume")
                setMusicVolume(std::stof(value.data()));
            else if (key == "master_volume")
                setMasterVolume(std::stof(value.data()));
            else if (key == "target_framerate")
                setTargetFramerate(std::stoul(value.data()));
            else if (key == "resolution") {
                int width;
                int height;

                if (value.find('x') == std::string::npos)
                    throw InvalidSettingsValue("Resolution must be of form '[width]x[height]'");
                width = std::stoi(value.data());
                height = std::stoi(value.data() + value.find('x') + 1);
                setResolution({width, height});
            } else if (key == "fullscreen") {
                bool fullscreen;
                std::istringstream(value.data()) >> fullscreen;
                setFullscreen(fullscreen || value == "true");
            } else if (key == "locale") {
                setLocale(value);
            } else {
                Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                    writer << "Unknown settings key '" << key << "' with value '" << value << "'";
                });
            }
        }

        void Settings::load()
        {
            loadDefaults();

            util::loadConfigFile(getSettingsFilePath(), [this](std::string_view key, std::string_view value) {
                try {
                    loadValue(key, value);
                } catch (std::exception &e) {
                    Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                        writer << "Exception occured when loading a setting value: '" << e.what() << "'";
                    });
                    Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                        writer << "Unable to load setting '" << key << "' with value '" << value
                               << "'. Default value will be used.";
                    });
                }
                return true;
            });
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

        void Settings::setMasterVolume(float volume)
        {
            if (volume < 0 || volume > 100)
                throw InvalidSettingsValue("Volumes must be between 0 and 100.");
            _masterVolume = volume;
        }

        float Settings::getMasterVolume() const { return _masterVolume; }

        void Settings::setTargetFramerate(unsigned int target) { _targetFramerate = target; }

        unsigned int Settings::getTargetFramerate() const { return _targetFramerate; }

        void Settings::setResolution(raylib::core::Vector2i resolution) { _resolution = resolution; }

        raylib::core::Vector2i Settings::getResolution() const { return _resolution; }

        void Settings::setFullscreen(bool fullscreen) { _fullscreen = fullscreen; }

        bool Settings::isFullscreen() const { return _fullscreen; }

        void Settings::setLocale(std::string_view locale) { _locale = locale; }

        std::string_view Settings::getLocale() const { return _locale; }

    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Settings &settings)
{
    stream << "# Bomberman settings" << std::endl << std::endl;
    stream << "sfx_volume=" << settings.getSfxVolume() << std::endl;
    stream << "music_volume=" << settings.getMusicVolume() << std::endl;
    stream << "master_volume=" << settings.getMasterVolume() << std::endl;
    stream << "target_framerate=" << settings.getTargetFramerate() << std::endl;
    stream << "resolution=" << settings.getResolution().x << "x" << settings.getResolution().y << std::endl;
    stream << "fullscreen=" << std::boolalpha << settings.isFullscreen() << std::endl;
    return stream << "locale=" << settings.getLocale() << std::endl;
}
