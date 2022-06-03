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
            //////// Keyboards keybinds
            /// Movements
            setKeyboardBinding(Key::Q, GameAction::MOVE_LEFT);
            setKeyboardBinding(Key::LEFT, GameAction::MOVE_LEFT);
            setKeyboardBinding(Key::Z, GameAction::MOVE_UP);
            setKeyboardBinding(Key::UP, GameAction::MOVE_UP);
            setKeyboardBinding(Key::D, GameAction::MOVE_RIGHT);
            setKeyboardBinding(Key::RIGHT, GameAction::MOVE_RIGHT);
            setKeyboardBinding(Key::S, GameAction::MOVE_DOWN);
            setKeyboardBinding(Key::DOWN, GameAction::MOVE_DOWN);
            /// Actions
            setKeyboardBinding(Key::E, GameAction::PLACE_BOMB);
            setKeyboardBinding(Key::P, GameAction::PAUSE);
            /// Menus
            setKeyboardBinding(Key::ENTER, GameAction::ACTION);
            setKeyboardBinding(Key::BACK, GameAction::BACK);

            /////// Gamepad keybinds
            /// Movements
            setGamepadBinding(Gamepad::Button::DPAD_FACE_LEFT, GameAction::MOVE_LEFT);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_X, GamepadInput::AxisDirection::Negative), GameAction::MOVE_LEFT);
            setGamepadBinding(Gamepad::Button::DPAD_FACE_UP, GameAction::MOVE_UP);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_Y, GamepadInput::AxisDirection::Positive), GameAction::MOVE_UP);
            setGamepadBinding(Gamepad::Button::DPAD_FACE_RIGHT, GameAction::MOVE_RIGHT);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_X, GamepadInput::AxisDirection::Positive), GameAction::MOVE_RIGHT);
            setGamepadBinding(Gamepad::Button::DPAD_FACE_DOWN, GameAction::MOVE_DOWN);
            setGamepadBinding(
                GamepadInput(Gamepad::Axis::LEFT_Y, GamepadInput::AxisDirection::Negative), GameAction::MOVE_DOWN);
            /// Actions
            setGamepadBinding(Gamepad::Button::FACE_DOWN, GameAction::PLACE_BOMB);
            setGamepadBinding(Gamepad::Button::MIDDLE_LEFT, GameAction::PAUSE);
            setGamepadBinding(Gamepad::Button::MIDDLE, GameAction::PAUSE);
            setGamepadBinding(Gamepad::Button::MIDDLE_RIGHT, GameAction::PAUSE);
            /// Menus
            setGamepadBinding(Gamepad::Button::FACE_DOWN, GameAction::ACTION); /// A on Xbox
            setGamepadBinding(Gamepad::Button::FACE_RIGHT, GameAction::BACK);  /// B on Xbox
        }

        void Keybinds::setKeyboardBinding(Key key, GameAction action) { _keyboardBindings[key] = action; }

        void Keybinds::unbindKey(Key key) { _keyboardBindings.erase(key); }

        void Keybinds::setGamepadBinding(const GamepadInput &gamepadInput, GameAction action)
        {
            _gamepadBindings[gamepadInput] = action;
        }

        void Keybinds::unbindGamepadInput(const GamepadInput &gamepadInput) { _gamepadBindings.erase(gamepadInput); }

        const std::map<Key, GameAction> &Keybinds::getKeyboardBindings() const { return _keyboardBindings; }

        const std::map<GamepadInput, GameAction> &Keybinds::getGamepadBindings() const { return _gamepadBindings; }

        const Keybinds &Keybinds::operator>>(std::ostream &stream) const
        {
            stream << "# Keyboard bindings" << std::endl;
            for (auto iter : _keyboardBindings)
                stream << "key:" << static_cast<int>(iter.first) << "=" << static_cast<int>(iter.second) << std::endl;
            stream << std::endl << "# Gamepad bindings" << std::endl;
            for (auto iter : _gamepadBindings)
                stream << "gamepad:" << iter.first.toString() << "=" << static_cast<int>(iter.second) << std::endl;
            return *this;
        }
    } // namespace settings
} // namespace game

std::ostream &operator<<(std::ostream &stream, const game::settings::Keybinds keybinds)
{
    keybinds >> stream;
    return stream;
}
