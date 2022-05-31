/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** KeyboardInput
*/

#ifndef GAME_SETTINGS_GAMEPADINPUT_HPP_
#define GAME_SETTINGS_GAMEPADINPUT_HPP_

#include "raylib/core/Gamepad.hpp"

namespace game
{
    namespace settings
    {
        class GamepadInput {
          public:
            enum class AxisDirection {
                None,
                Negative,
                Positive,
            };

            GamepadInput(raylib::core::Gamepad::Button button);
            GamepadInput(raylib::core::Gamepad::Axis axis, AxisDirection direction);
            ~GamepadInput() = default;

            bool isButton() const;

            std::string toString() const;

            bool operator<(const GamepadInput &other) const;
            bool operator==(const GamepadInput &other) const;

          private:
            raylib::core::Gamepad::Button _button;
            raylib::core::Gamepad::Axis _axis;
            AxisDirection _axisDirection;
        };
    } // namespace settings
} // namespace game

#endif /* !GAME_SETTINGS_GAMEPADINPUT_HPP_ */
