/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Keybinds
*/

#include "Keybinds.hpp"
#include <exception>

using Key = raylib::core::Keyboard::Key;
using Gamepad = raylib::core::Gamepad;

namespace game
{
    namespace settings
    {
        Keybinds::Keybinds() { loadDefaults(); }

        void Keybinds::loadDefaults()
        {
            clear();

            //////// Keyboards keybinds
            /// Movements
            setKeyboardBinding(Key::A, GameAction::MOVE_LEFT);
            setKeyboardBinding(Key::W, GameAction::MOVE_UP);
            setKeyboardBinding(Key::D, GameAction::MOVE_RIGHT);
            setKeyboardBinding(Key::S, GameAction::MOVE_DOWN);
            /// Actions
            setKeyboardBinding(Key::SPACE, GameAction::PLACE_BOMB);
            setKeyboardBinding(Key::F, GameAction::ACTIVATE_ITEM);
            setKeyboardBinding(Key::Q, GameAction::PREVIOUS_ACTIVABLE);
            setKeyboardBinding(Key::E, GameAction::NEXT_ACTIVABLE);
            setKeyboardBinding(Key::P, GameAction::PAUSE);
            /// Menus
            setKeyboardBinding(Key::SPACE, GameAction::ACTION);
            setKeyboardBinding(Key::BACK, GameAction::BACK);

            /////// Gamepad keybinds
            /// Movements
            setGamepadBinding(Gamepad::Button::DPAD_FACE_LEFT, GameAction::MOVE_LEFT);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_X, GamepadInput::AxisDirection::Negative), GameAction::MOVE_LEFT);
            setGamepadBinding(Gamepad::Button::DPAD_FACE_UP, GameAction::MOVE_UP);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_Y, GamepadInput::AxisDirection::Negative), GameAction::MOVE_UP);
            setGamepadBinding(Gamepad::Button::DPAD_FACE_RIGHT, GameAction::MOVE_RIGHT);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_X, GamepadInput::AxisDirection::Positive), GameAction::MOVE_RIGHT);
            setGamepadBinding(Gamepad::Button::DPAD_FACE_DOWN, GameAction::MOVE_DOWN);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_Y, GamepadInput::AxisDirection::Positive), GameAction::MOVE_DOWN);
            /// Actions
            setGamepadBinding(Gamepad::Button::FACE_DOWN, GameAction::PLACE_BOMB);
            setGamepadBinding(Gamepad::Button::RIGHT_TRIGGER, GameAction::ACTIVATE_ITEM);
            setGamepadBinding(Gamepad::Button::LEFT_BUMPER, GameAction::PREVIOUS_ACTIVABLE);
            setGamepadBinding(Gamepad::Button::RIGHT_BUMPER, GameAction::NEXT_ACTIVABLE);
            setGamepadBinding(Gamepad::Button::MIDDLE_LEFT, GameAction::PAUSE);
            setGamepadBinding(Gamepad::Button::MIDDLE, GameAction::PAUSE);
            setGamepadBinding(Gamepad::Button::MIDDLE_RIGHT, GameAction::PAUSE);
            /// Menus
            setGamepadBinding(Gamepad::Button::FACE_DOWN, GameAction::ACTION); /// A on Xbox
            setGamepadBinding(Gamepad::Button::FACE_RIGHT, GameAction::BACK);  /// B on Xbox
        }

        void Keybinds::clear()
        {
            _keyboardBindings.clear();
            _gamepadBindings.clear();
            /// Do not let the user configure this action
            setGamepadBinding(Gamepad::Button::MIDDLE_LEFT, GameAction::DISCONNECT);
        }

        void Keybinds::unbindAction(GameAction action, bool keyboard)
        {
            if (keyboard) {
                for (size_t i = _keyboardBindings.size(); i > 0; i--) {
                    if (_keyboardBindings[i - 1].action == action)
                        _keyboardBindings.erase(_keyboardBindings.begin() + (i - 1));
                }
            } else {
                for (size_t i = _gamepadBindings.size(); i > 0; i--)
                    if (_gamepadBindings[i - 1].action == action)
                        _gamepadBindings.erase(_gamepadBindings.begin() + (i - 1));
            }
        }

        void Keybinds::setKeyboardBinding(Key key, GameAction action, bool exclusive)
        {
            if (exclusive)
                unbindAction(action, true);
            else
                unbindKey(key, action);
            _keyboardBindings.emplace_back(key, action);
        }

        void Keybinds::unbindKey(Key key, GameAction action)
        {
            for (size_t i = _keyboardBindings.size(); i > 0; i--) {
                auto &bind = _keyboardBindings[i - 1];
                if (bind.key == key && (action == GameAction::NONE || bind.action == action))
                    _keyboardBindings.erase(_keyboardBindings.begin() + (i - 1));
            }
        }

        void Keybinds::setGamepadBinding(const GamepadInput &gamepadInput, GameAction action, bool exclusive)
        {
            if (exclusive)
                unbindAction(action, false);
            else
                unbindGamepadInput(gamepadInput, action);
            _gamepadBindings.emplace_back(gamepadInput, action);
        }

        void Keybinds::unbindGamepadInput(const GamepadInput &gamepadInput, GameAction action)
        {
            for (size_t i = _gamepadBindings.size(); i > 0; i--) {
                const GamepadBind &bind = _gamepadBindings[i - 1];
                if ((bind.input <=> gamepadInput == std::strong_ordering::equal)
                    && (action == GameAction::NONE || bind.action == action))
                    _gamepadBindings.erase(_gamepadBindings.begin() + (i - 1));
            }
        }

        const std::vector<Keybinds::KeyboardBind> &Keybinds::getKeyboardBindings() const { return _keyboardBindings; }

        const std::vector<Keybinds::GamepadBind> &Keybinds::getGamepadBindings() const { return _gamepadBindings; }

        const Keybinds &Keybinds::operator>>(std::ostream &stream) const
        {
            stream << "# Keyboard bindings" << std::endl;
            for (auto iter : _keyboardBindings)
                stream << "key:" << static_cast<int>(iter.key) << "=" << static_cast<int>(iter.action) << std::endl;
            stream << std::endl << "# Gamepad bindings" << std::endl;
            for (auto iter : _gamepadBindings)
                stream << "gamepad:" << iter.input.toString() << "=" << static_cast<int>(iter.action) << std::endl;
            return *this;
        }
    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Keybinds keybinds)
{
    keybinds >> stream;
    return stream;
}
