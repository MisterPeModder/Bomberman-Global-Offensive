/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** User
*/

#include "User.hpp"

namespace game
{
    User::User(size_t id, int gamepadId) : _profile(id), _gamepadId(gamepadId)
    {
        setAvailable(false);
        _lastActions.fill(0);
    }

    void User::setKeyboard() { _gamepadId = -1; }

    bool User::isKeyboard() const { return _gamepadId < 0; }

    void User::setGamepadId(int id) { _gamepadId = id; }

    int User::getGamepadId() const { return _gamepadId; }

    void User::setId(size_t id) { _profile.load(id); }

    size_t User::getId() const { return _profile.getId(); }

    void User::setAvailable(bool available) { _available = available; }

    bool User::isAvailable() const { return _available; }

    void User::fillActions()
    {
        std::queue<GameAction> empty;
        float actionValue;

        _changedActions.swap(empty);
        for (size_t i = 0; i < _lastActions.size(); i++) {
            actionValue = getActionValue(static_cast<GameAction>(i + 1));

            if (actionValue != _lastActions[i]) {
                _changedActions.push(static_cast<GameAction>(i + 1));
                _lastActions[i] = actionValue;
            }
        }
    }

    float User::getActionValue(GameAction action)
    {
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
} // namespace game