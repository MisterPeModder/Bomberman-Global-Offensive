/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Gamepad
*/

#include "Gamepad.hpp"

namespace raylib
{
    namespace core
    {
        Gamepad::Gamepad(int id) : _id(id) {}

        Gamepad &Gamepad::operator=(int id)
        {
            _id = id;
            return *this;
        }

        bool Gamepad::isAvailable() const { return IsGamepadAvailable(_id); }

        std::string_view Gamepad::getName() const { return GetGamepadName(_id); }

        bool Gamepad::isButtonPressed(Button button) const
        {
            return IsGamepadButtonPressed(_id, static_cast<int>(button));
        }

        bool Gamepad::isButtonDown(Button button) const { return IsGamepadButtonDown(_id, static_cast<int>(button)); }

        bool Gamepad::isButtonReleased(Button button) const
        {
            return IsGamepadButtonReleased(_id, static_cast<int>(button));
        }

        bool Gamepad::isButtonUp(Button button) const { return IsGamepadButtonUp(_id, static_cast<int>(button)); }

        Gamepad::Button Gamepad::getButtonPressed() { return static_cast<Button>(GetGamepadButtonPressed()); }

        int Gamepad::getAxisCount() const { return GetGamepadAxisCount(_id); }

        float Gamepad::getAxisMovement(Axis axis) const { return GetGamepadAxisMovement(_id, static_cast<int>(axis)); }

        Vector2 Gamepad::getJoystickDirection(Joystick joystick) const
        {
            if (joystick == Joystick::LEFT)
                return {getAxisMovement(Axis::LEFT_X), getAxisMovement(Axis::LEFT_Y)};
            else
                return {getAxisMovement(Axis::RIGHT_X), getAxisMovement(Axis::RIGHT_Y)};
        }

        int Gamepad::setMappings(std::string_view mappings) const { return SetGamepadMappings(mappings.data()); }
    } // namespace core
} // namespace raylib
