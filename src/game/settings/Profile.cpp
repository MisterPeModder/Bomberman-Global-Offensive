/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Profile
*/

#include "Profile.hpp"
#include <fstream>
#include "util/util.hpp"

namespace game
{
    namespace settings
    {
        Profile::Profile(size_t id) : _id(id) { _name = "Player " + std::to_string(id + 1); }

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

        std::filesystem::path Profile::getFilesDirectory() { return util::makePath("settings", "profiles"); }

        std::filesystem::path Profile::getFilepath() const
        {
            return util::makePath("settings", "profiles", getFilename());
        }

        std::string Profile::getFilename() const { return "player_" + std::to_string(_id) + ".cfg"; }

        size_t Profile::getId() const { return _id; }

        void Profile::setName(std::string_view name) { _name = name; }

        std::string_view Profile::getName() const { return _name; }

        Keybinds &Profile::getKeybinds() { return _keybinds; }

        const Keybinds &Profile::getKeybinds() const { return _keybinds; }
    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Profile &profile)
{
    stream << "# Profile of player " << profile.getId() << std::endl << std::endl;
    stream << "name=" << profile.getName() << std::endl << std::endl;
    return stream << profile.getKeybinds();
}
