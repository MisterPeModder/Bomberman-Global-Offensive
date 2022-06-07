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
        for (size_t i = 0; i < PlayerCount; i++)
            _users[i].setId(i);
    }

    const User &Users::operator[](UserId id) const { return _users[id]; }

    User &Users::operator[](UserId id) { return _users[id]; }

    Users::ActionEvent Users::getNextAction()
    {
        for (size_t i = 0; i < PlayerCount; i++) {
            GameAction action = _users[i].getChangedAction();

            if (action != GameAction::NONE)
                return ActionEvent{static_cast<UserId>(i), action, _users[i].getActionValue(action)};
        }
        return {PlayerCount, GameAction::NONE, 0};
    }
} // namespace game