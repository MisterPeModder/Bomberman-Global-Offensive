/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GamepadInput
*/

#include "GamepadInput.hpp"
#include <string>

namespace game
{
    namespace settings
    {
        GamepadInput::GamepadInput(raylib::core::Gamepad::Button button) : _button(button) {}

        GamepadInput::GamepadInput(raylib::core::Gamepad::Axis axis, AxisDirection direction)
            : _button(raylib::core::Gamepad::Button::UNKNOWN), _axis(axis), _axisDirection(direction)
        {
        }

        raylib::core::Gamepad::Button GamepadInput::getButton() const { return _button; }

        raylib::core::Gamepad::Axis GamepadInput::getAxis() const { return _axis; }

        GamepadInput::AxisDirection GamepadInput::getAxisDirection() const { return _axisDirection; }

        bool GamepadInput::isButton() const { return _button != raylib::core::Gamepad::Button::UNKNOWN; }

        std::string GamepadInput::toString() const
        {
            if (isButton())
                return std::to_string(static_cast<int>(_button));
            else
                return std::to_string(static_cast<int>(_axis)) + ':' + std::to_string(static_cast<int>(_axisDirection));
        }

        bool GamepadInput::operator<(const GamepadInput &other) const
        {
            if (isButton() != other.isButton())
                return isButton();
            if (isButton())
                return _button < other._button;
            else {
                if (_axis != other._axis)
                    return _axis < other._axis;
                else
                    return _axisDirection < other._axisDirection;
            }
        }

        bool GamepadInput::operator==(const GamepadInput &other) const
        {
            return isButton() == other.isButton()
                && ((isButton() && _button == other._button)
                    || (!isButton() && _axis == other._axis && _axisDirection == other._axisDirection));
        }
    } // namespace settings
} // namespace game