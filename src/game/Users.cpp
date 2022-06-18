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
        return getGamepadJoin();
    }

    Users::ActionEvent Users::getGamepadJoin()
    {
        size_t usersCount = static_cast<size_t>(User::UserId::UserCount);

        for (size_t i = 0; i < usersCount; i++) {
            auto gamepad = raylib::core::Gamepad(i);
            if (!gamepad.isAvailable())
                continue;
            bool unbindGamepad = true;
            for (size_t j = 0; j < usersCount; j++) {
                if (_users[j].isAvailable() && static_cast<size_t>(_users[j].getGamepadId()) == i) {
                    unbindGamepad = false;
                    break;
                }
            }
            if (!unbindGamepad)
                continue;
            if (gamepad.isButtonReleased(raylib::core::Gamepad::Button::FACE_DOWN))
                return {static_cast<User::UserId>(i), GameAction::JOIN, 1};
        }
        return {User::UserId::UserCount, GameAction::NONE, 0};
    }
} // namespace game
