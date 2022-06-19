/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** User
*/

#include "User.hpp"
#include <algorithm>

#include <algorithm>

namespace game
{
    User::User(UserId id, int gamepadId) : _gamepadId(gamepadId), _profile(static_cast<size_t>(id))
    {
        setAvailable(false);
        _lastActions.fill(0);
    }

    void User::setKeyboard() { _gamepadId = -1; }

    bool User::isKeyboard() const { return _gamepadId < 0; }

    void User::setGamepadId(int id)
    {
        _gamepadId = id;
        updateActions(false);
    }

    int User::getGamepadId() const { return _gamepadId; }

    void User::setId(UserId id) { _profile.load(static_cast<size_t>(id)); }

    User::UserId User::getId() const { return static_cast<UserId>(_profile.getId()); }

    void User::setAvailable(bool available) { _available = available; }

    bool User::isAvailable() const { return _available; }

    void User::updateActions(bool fillChanged)
    {
        clearPendingActions();
        for (size_t i = 0; i < _lastActions.size(); i++) {
            float actionValue = getActionValue(static_cast<GameAction>(i + 1), true);

            if (fillChanged && actionValue != _lastActions[i])
                _changedActions.push(static_cast<GameAction>(i + 1));
            _lastActions[i] = actionValue;
        }
    }

    void User::clearPendingActions()
    {
        std::queue<GameAction> empty;

        _changedActions.swap(empty);
    }

    GameAction User::getChangedAction()
    {
        if (_changedActions.empty())
            updateActions();
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
            auto &binds = _profile.getKeybinds().getKeyboardBindings();

            return (binds.end() != std::find_if(binds.begin(), binds.end(), [&](auto iter) {
                return (iter.action == action && raylib::core::Keyboard::isKeyDown(iter.key));
            }));
        } else {
            auto &binds = _profile.getKeybinds().getGamepadBindings();
            raylib::core::Gamepad gamepad(_gamepadId);

            for (auto iter : binds) {
                if (iter.action != action)
                    continue;
                if (iter.input.isButton()) {
                    if (gamepad.isButtonDown(iter.input.getButton()))
                        return 1;
                } else {
                    float axisValue = iter.input.getAxisAbsoluteValue(gamepad.getAxisMovement(iter.input.getAxis()));

                    if (axisValue > res)
                        res = axisValue;
                }
            }
        }
        return res;
    }

    const settings::Profile &User::getProfile() const { return _profile; }

    settings::Profile &User::getProfile() { return _profile; }

    const settings::Keybinds &User::getKeybinds() const { return _profile.getKeybinds(); }

    settings::Keybinds &User::getKeybinds() { return _profile.getKeybinds(); }
} // namespace game
