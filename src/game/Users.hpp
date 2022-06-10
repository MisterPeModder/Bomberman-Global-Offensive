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

      private:
        std::array<User, static_cast<size_t>(User::UserId::UserCount)> _users;
    };
} // namespace game

#endif /* !USERS_HPP_ */
