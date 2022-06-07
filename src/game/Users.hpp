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

namespace game
{
    class Users {
      public:
        struct ActionEvent {
            User::UserId user;
            GameAction action;
            /// 0 -> 1
            /// 0 means released
            /// 1 means pressed
            /// intermediate values are for axis
            float value;
        };
        Users();
        ~Users() = default;

        User &operator[](User::UserId id);
        const User &operator[](User::UserId id) const;

        ActionEvent getNextAction();

      private:
        std::array<User, static_cast<size_t>(User::UserId::UserCount)> _users;
    };
} // namespace game

#endif /* !USERS_HPP_ */
