/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Users
*/

#ifndef USERS_HPP_
#define USERS_HPP_

#include "User.hpp"

namespace game
{

    class Users {
      public:
        enum UserId { Player1, Player2, Player3, Player4, PlayerCount };
        struct ActionEvent {
            UserId user;
            GameAction action;
            /// 0 -> 1
            /// 0 means released
            /// 1 means pressed
            /// intermediate values are for axis
            float value;
        };
        Users();
        ~Users() = default;

        User &operator[](UserId id);
        const User &operator[](UserId id) const;

        ActionEvent getNextAction();

      private:
        User _users[UserId::PlayerCount];
    };
} // namespace game

#endif /* !USERS_HPP_ */
