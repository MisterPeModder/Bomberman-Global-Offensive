/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GamepadInput
*/

#include "GamepadInput.hpp"

namespace game
{
    namespace settings
    {
        GamepadInput::GamepadInput(raylib::core::Gamepad::Button button) : _button(button) {}

        GamepadInput::GamepadInput(raylib::core::Gamepad::Axis axis, AxisDirection direction)
            : _button(raylib::core::Gamepad::Button::UNKNOWN), _axis(axis), _axisDirection(direction)
        {
        }

        bool GamepadInput::isButton() const { return _button != raylib::core::Gamepad::Button::UNKNOWN; }

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