/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Profile
*/

#include "Profile.hpp"
#include <fstream>
#include <regex>
#include "Logger.hpp"
#include "util/util.hpp"

namespace game
{
    namespace settings
    {
        Profile::Profile(size_t id) : _id(id) { load(); }

        void Profile::save() const
        {
            std::filesystem::path path = getFilepath();
            std::ofstream file;

            std::filesystem::create_directories(getFilesDirectory());
            file.open(path, std::ios_base::out);
            if (!file.is_open())
                throw std::runtime_error("Unable to save the profile file '" + path.generic_string() + "'");
            file << *this;
            file.close();
        }

        void Profile::load()
        {
            _name = "Player " + std::to_string(_id + 1);
            clearBindings();

            if (!util::loadConfigFile(getFilepath(), [this](std::string_view key, std::string_view value) {
                    try {
                        loadValue(key, value);
                    } catch (std::exception &e) {
                        Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                            writer << "Exception occured when loading a profile value: '" << e.what() << "'";
                        });
                        Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                            writer << "Unable to load profile attribute '" << key << "' with value '" << value
                                   << "'. Default values will be used for the profile.";
                        });
                        loadDefaults();
                        return false;
                    }
                    return true;
                }))
                loadDefaults();
        }

        void Profile::load(size_t id)
        {
            _id = id;
            load();
        }

        void Profile::loadDefaults()
        {
            _name = "Player " + std::to_string(_id + 1);
            _keybinds.loadDefaults();
        }

        void Profile::clearBindings() { _keybinds.clear(); }

        std::filesystem::path Profile::getFilesDirectory() { return util::makePath("settings", "profiles"); }

        std::filesystem::path Profile::getFilepath() const
        {
            return util::makePath(getFilesDirectory(), getFilename());
        }

        std::string Profile::getFilename() const { return "player_" + std::to_string(_id) + ".cfg"; }

        size_t Profile::getId() const { return _id; }

        void Profile::setName(std::string_view name) { _name = name; }

        std::string_view Profile::getName() const { return _name; }

        Keybinds &Profile::getKeybinds() { return _keybinds; }

        const Keybinds &Profile::getKeybinds() const { return _keybinds; }

        void Profile::loadValue(std::string_view key, std::string_view value)
        {
            static std::regex keyBind("key:[0-9]+");
            static std::regex gamepadBind("gamepad:[0-9]+(:[0-9])?");
            static std::regex gamepadAxisBind("gamepad:[0-9]+:[0-9]");

            if (key == "name")
                setName(value);
            else if (std::regex_match(key.data(), keyBind)) {
                _keybinds.setKeyboardBinding(
                    static_cast<raylib::core::Keyboard::Key>(std::stoi(key.data() + key.find(':') + 1)),
                    static_cast<GameAction>(std::stoi(value.data())));
            } else if (std::regex_match(key.data(), gamepadBind)) {
                if (std::regex_match(key.data(), gamepadAxisBind)) {
                    size_t off = key.find(':') + 1;
                    _keybinds.setGamepadBinding(
                        GamepadInput(static_cast<raylib::core::Gamepad::Axis>(std::stoi(key.data() + off)),
                            static_cast<GamepadInput::AxisDirection>(std::stoi(key.data() + key.find(':', off) + 1))),
                        static_cast<GameAction>(std::stoi(value.data())));
                } else {
                    _keybinds.setGamepadBinding(
                        static_cast<raylib::core::Gamepad::Button>(std::stoi(key.data() + key.find(':') + 1)),
                        static_cast<GameAction>(std::stoi(value.data())));
                }
            } else {
                Logger::logger.log(Logger::Severity::Warning, [&](std::ostream &writer) {
                    writer << "Unknown settings key '" << key << "' with value '" << value << "'";
                });
            }
        }

    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Profile &profile)
{
    stream << "# Profile of player " << profile.getId() << std::endl << std::endl;
    stream << "name=" << profile.getName() << std::endl << std::endl;
    return stream << profile.getKeybinds();
}
