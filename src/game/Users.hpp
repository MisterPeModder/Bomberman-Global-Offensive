/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Users
*/

#ifndef USERS_HPP_
#define USERS_HPP_

#include <array>
#include "User.hpp"
#include "ecs/resource/Resource.hpp"

namespace game
{
    /// Resource allowing to get users actions using the keybinds.
    class Users final : public ecs::Resource {
      public:
        /// Event send by @ref getNextAction() when an action changed.
        struct ActionEvent {
            User::UserId user; ///  User Id of the user whose action changed.
            GameAction action; /// Action changed.
            float value;       /// New value of the action. 0 means released, 1 means pressed.
                               /// Intermediate values are for gamepad axis.
        };

        /// Create a new Users object.
        Users();

        /// Construct a copy of a Users object.
        ///
        /// @param other users to copy.
        Users(const Users &other) = default;

        /// Destroys the users object.
        ~Users() = default;

        /// Copy a Users object.
        ///
        /// @param other object to copy.
        /// @return Users& @b this.
        Users &operator=(const Users &other) = default;

        /// Get the User with the matching UserId.
        ///
        /// @param UserId user id.
        /// @return User& user.
        User &operator[](User::UserId id);

        /// Get the User with the matching UserId.
        ///
        /// @param UserId user id.
        /// @return const User& user.
        const User &operator[](User::UserId id) const;

        /// Get the Next Action event.
        ///
        /// @return ActionEvent next action event. action is set to None if there is no more actions.
        ActionEvent getNextAction();

        bool isGamepadUsed(int gamepadId) const;

        /// Find the first available gamepad which has @ref getButtonPressed() button down and is not used by any
        /// user.
        ///
        /// @return int gamepad id, -1 if no joining gamepad at the moment.
        int getJoiningGamepad() const;

        /// Get the number of available (connected) users.
        ///
        /// @return unsigned int number of connected users.
        unsigned int getAvailableUsers() const;

        /// Connect a new user to a given control.
        /// @note If gamepadId is negative, the user will be connected to the keyboard.
        ///
        /// @param gamepadId Control id.
        void connectUser(int gamepadId);

        /// Disconnect a user.
        /// @note All following users will be shifted to the left (user 3 become user 2 with profile 2 etc)
        ///
        /// @param user User to disconnect.
        void disconnectUser(User::UserId user);

        /// Call @ref User::updateActions() for each user.
        ///
        /// @param fillChanged Set to true to fill the changed actions queueq.
        void updateActions(bool fillChanged = true);

      private:
        std::array<User, static_cast<size_t>(User::UserId::UserCount)> _users;
    };
} // namespace game

#endif /* !USERS_HPP_ */
