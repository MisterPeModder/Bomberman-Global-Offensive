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

    User &Users::getUser(UserId id) { return _users[id]; }

    void Users::fillActions()
    {
        /// Clear queue + Gamepad Inputs
        for (size_t i = 0; i < PlayerCount; i++)
            _users[i].fillActions();

        /// Keyboards Inputs
        raylib::core::Keyboard::Key key;
        while ((key = raylib::core::Keyboard::getKeyPressed()) != raylib::core::Keyboard::Key::NONE) {
            for (size_t i = 0; i < PlayerCount; i++)
                if (_users[i].keyToQueuedAction(key))
                    break;
        }
    }

    std::pair<Users::UserId, GameAction> Users::getNextAction()
    {
        for (size_t i = 0; i < PlayerCount; i++) {
            GameAction action = _users[i].getNextAction();

            if (action != GameAction::NONE)
                return {static_cast<UserId>(i), action};
        }
        return {PlayerCount, GameAction::NONE};
    }
} // namespace game