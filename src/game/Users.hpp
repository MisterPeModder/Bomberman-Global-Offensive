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
        Users();
        ~Users() = default;

        User &getUser(UserId id);

        void fillActions();

        std::pair<UserId, GameAction> getNextAction();

      private:
        User _users[UserId::PlayerCount];
    };
} // namespace game

#endif /* !USERS_HPP_ */
