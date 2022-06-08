/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** User
*/

#include "User.hpp"

namespace game
{
    User::User(UserId id, int gamepadId) : _gamepadId(gamepadId), _profile(static_cast<size_t>(id))
    {
        setAvailable(false);
        _lastActions.fill(0);
    }

    void User::setKeyboard() { _gamepadId = -1; }

    bool User::isKeyboard() const { return _gamepadId < 0; }

    void User::setGamepadId(int id) { _gamepadId = id; }

    int User::getGamepadId() const { return _gamepadId; }

    void User::setId(UserId id) { _profile.load(static_cast<size_t>(id)); }

    User::UserId User::getId() const { return static_cast<UserId>(_profile.getId()); }

    void User::setAvailable(bool available) { _available = available; }

    bool User::isAvailable() const { return _available; }

    void User::fillActions()
    {
        std::queue<GameAction> empty;
        float actionValue;

        _changedActions.swap(empty);
        for (size_t i = 0; i < _lastActions.size(); i++) {
            actionValue = getActionValue(static_cast<GameAction>(i + 1), true);

            if (actionValue != _lastActions[i]) {
                _changedActions.push(static_cast<GameAction>(i + 1));
                _lastActions[i] = actionValue;
            }
        }
    }

    GameAction User::getChangedAction()
    {
        if (_changedActions.empty())
            fillActions();
        if (_changedActions.empty())
            return GameAction::NONE;

        GameAction action = _changedActions.front();
        _changedActions.pop();
        return action;
    }

    float User::getActionValue(GameAction action, bool update)
    {
        if (!update)
            return _lastActions[static_cast<size_t>(action) - 1];
        float res = 0.f;

        if (isKeyboard()) {
            auto binds = _profile.getKeybinds().getKeyboardBindings();

            return (binds.end() != std::find_if(binds.begin(), binds.end(), [&](auto iter) {
                return (iter.second == action && raylib::core::Keyboard::isKeyDown(iter.first));
            }));
        } else {
            auto binds = _profile.getKeybinds().getGamepadBindings();
            raylib::core::Gamepad gamepad(_gamepadId);

            for (auto iter = binds.begin(); iter != binds.end(); ++iter) {
                if (iter->second != action)
                    continue;
                if (iter->first.isButton()) {
                    if (gamepad.isButtonDown(iter->first.getButton()))
                        return 1;
                } else {
                    float axisValue = iter->first.getAxisAbsoluteValue(gamepad.getAxisMovement(iter->first.getAxis()));

                    if (axisValue > res)
                        res = axisValue;
                }
            }
        }
        return res;
    }
} // namespace game
