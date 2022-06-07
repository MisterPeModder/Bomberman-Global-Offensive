/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** User
*/

#include "User.hpp"

namespace game
{
    User::User(size_t id, int gamepadId) : _profile(id), _gamepadId(gamepadId) { setAvailable(false); }

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

        _actions.swap(empty);
        if (!isKeyboard()) {
            auto gamepadBinds = _profile.getKeybinds().getGamepadBindings();
            raylib::core::Gamepad gamepad(_gamepadId);

            for (auto iter = gamepadBinds.begin(); iter != gamepadBinds.end(); ++iter) {
                if (iter->first.isButton()) {
                    if (gamepad.isButtonPressed(iter->first.getButton()))
                        _actions.push(iter->second);
                } else if (iter->first.getAxisAbsoluteValue(gamepad.getAxisMovement(iter->first.getAxis())) > 0.f)
                    _actions.push(iter->second);
            }
        }
    }

    bool User::isActionUsed(GameAction action)
    {
        if (isKeyboard()) {
            auto binds = _profile.getKeybinds().getKeyboardBindings();

            return (binds.end() != std::find_if(binds.begin(), binds.end(), [&](auto iter) {
                return (iter.second == action && raylib::core::Keyboard::isKeyDown(iter.first));
            }));
        } else {
            auto binds = _profile.getKeybinds().getGamepadBindings();
            raylib::core::Gamepad gamepad(_gamepadId);

            if (binds.end() != std::find_if(binds.begin(), binds.end(), [&](auto iter) {
                    if (iter.second != action)
                        return false;
                    return ((iter.first.isButton() && gamepad.isButtonDown(iter.first.getButton()))
                        || (!iter.first.isButton()
                            && iter.first.getAxisAbsoluteValue(gamepad.getAxisMovement(iter.first.getAxis())) > 0.f));
                }))
                return true;
        }
        return false;
    }

    GameAction User::getNextAction()
    {
        if (_actions.empty())
            return GameAction::NONE;

        GameAction action = _actions.front();
        _actions.pop();
        return action;
    }

    bool User::keyToQueuedAction(raylib::core::Keyboard::Key key)
    {
        auto keyboardBinds = _profile.getKeybinds().getKeyboardBindings();

        if (keyboardBinds.find(key) == keyboardBinds.end())
            return false;
        _actions.push(keyboardBinds.at(key));
        return true;
    }
} // namespace game