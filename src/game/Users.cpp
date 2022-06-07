/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Users
*/

#include "Users.hpp"

namespace game
{
    Users::Users()
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++)
            _users[i].setId(static_cast<User::UserId>(i));
    }

    const User &Users::operator[](User::UserId id) const { return _users[static_cast<size_t>(id)]; }

    User &Users::operator[](User::UserId id) { return _users[static_cast<size_t>(id)]; }

    Users::ActionEvent Users::getNextAction()
    {
        for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++) {
            GameAction action = _users[i].getChangedAction();

            if (action != GameAction::NONE)
                return ActionEvent{static_cast<User::UserId>(i), action, _users[i].getActionValue(action)};
        }
        return {User::UserId::UserCount, GameAction::NONE, 0};
    }
} // namespace game