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
            /// Construct and load a Profile.
            ///
            /// @param id id of the profile.
            Profile(size_t id = 0);

            /// Construct a copy of a Profile.
            ///
            /// @param other profile to copy.
            Profile(const Profile &other) = default;

            /// Destroy the Profile.
            ~Profile() = default;

            /// Copy a profile.
            ///
            /// @param other profile to copy.
            /// @return Profile& @b this.
            Profile &operator=(const Profile &other) = default;

            /// Save the profile in the file @ref getFilepath().
            void save() const;

            /// Load the profile from the file @ref getFilepath().
            /// @note Default values will be loaded if the file doesn't exist or has invalid attributes.
            void load();

            /// Change the profile id and load the corresponding file with @ref load().
            ///
            /// @param id new id of the profile.
            void load(size_t id);

            /// Load the default profile parameters.
            void loadDefaults();

            /// Get the profile files directory.
            ///
            /// @retval std::filesystem::path "settings/profiles"
            static std::filesystem::path getFilesDirectory();

            /// Get the Filepath of the profile.
            /// @note This is the concatenation of @ref getFilesDirectory() and @ref getFilename()
            ///
            /// @return std::filesystem::path filepath of the profile.
            std::filesystem::path getFilepath() const;

            /// Get the name of the profile file.
            ///
            /// @retval std::string "player_[id].cfg"
            std::string getFilename() const;

            /// Get the profile id.
            ///
            /// @return size_t profile id.
            size_t getId() const;

            /// Set the profile name.
            ///
            /// @param name new name.
            void setName(std::string_view name);

            /// Get the Name of the profile.
            /// @note By default it is "Player [id + 1]".
            ///
            /// @return std::string_view profile name.
            std::string_view getName() const;

            /// Get the Keybinds.
            ///
            /// @return Keybinds& keybinds.
            Keybinds &getKeybinds();

            /// Get the Keybinds.
            ///
            /// @return const Keybinds& keybinds.
            const Keybinds &getKeybinds() const;

          private:
            void loadValue(std::string_view key, std::string_view value);

            Keybinds _keybinds;
            std::string _name;
            size_t _id;
        };
    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Profile &profile);

#endif /* !GAME_SETTINGS_PROFILE_HPP_ */
