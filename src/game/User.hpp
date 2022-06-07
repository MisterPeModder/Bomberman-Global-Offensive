/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** User
*/

#ifndef GAME_USER_HPP_
#define GAME_USER_HPP_

#include <queue>
#include "settings/Profile.hpp"

namespace game
{
    class User {
      public:
        User(size_t id = 0, int gamepadId = -1);
        ~User() = default;

        void setKeyboard();
        bool isKeyboard() const;

        void setGamepadId(int id);
        int getGamepadId() const;

        void setId(size_t id);
        size_t getId() const;

        void setAvailable(bool available);
        bool isAvailable() const;

        bool keyToQueuedAction(raylib::core::Keyboard::Key key);
        void fillActions();
        bool isActionUsed(GameAction action);
        GameAction getNextAction();

      private:
        int _gamepadId;
        bool _available;
        settings::Profile _profile;

        std::queue<GameAction> _actions;
    };
} // namespace game

#endif /* !GAME_USER_HPP_ */
