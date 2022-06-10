/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GamepadInput
*/

#include "GamepadInput.hpp"
#include <algorithm>
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

        float GamepadInput::getAxisAbsoluteValue(float value) const
        {
            if (_axisDirection == AxisDirection::None)
                return 0;
            if (_axisDirection == AxisDirection::Negative)
                return abs(std::min(value, 0.f));
            else
                return std::max(0.f, value);
        }

        bool GamepadInput::isButton() const { return _button != raylib::core::Gamepad::Button::UNKNOWN; }

        std::string GamepadInput::toString() const
        {
            if (isButton())
                return std::to_string(static_cast<int>(_button));
            else
                return std::to_string(static_cast<int>(_axis)) + ':' + std::to_string(static_cast<int>(_axisDirection));
        }

        std::strong_ordering GamepadInput::operator<=>(const GamepadInput &other) const
        {
            if (isButton() != other.isButton())
                return isButton() ? std::strong_ordering::less : std::strong_ordering::greater;
            if (isButton())
                return _button <=> other._button;
            else {
                if (_axis != other._axis)
                    return _axis <=> other._axis;
                else
                    return _axisDirection <=> other._axisDirection;
            }
        }
    } // namespace settings
} // namespace game
