/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Profile
*/

#ifndef GAME_SETTINGS_PROFILE_HPP_
#define GAME_SETTINGS_PROFILE_HPP_

#include <filesystem>
#include <ostream>
#include <string>
#include "Keybinds.hpp"

namespace game
{
    namespace settings
    {
        class Profile {
          public:
            Profile(size_t id = 0);
            ~Profile() = default;

            void save() const;

            static std::filesystem::path getFilesDirectory();
            std::filesystem::path getFilepath() const;
            std::string getFilename() const;

            size_t getId() const;

            void setName(std::string_view name);
            std::string_view getName() const;

            Keybinds &getKeybinds();
            const Keybinds &getKeybinds() const;

          private:
            Keybinds _keybinds;
            std::string _name;
            size_t _id;
        };
    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Profile &profile);

#endif /* !GAME_SETTINGS_PROFILE_HPP_ */
