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
        /// Define a gamepad input. An input can be a button or a specific axis direction (Ex: the joystick left
        /// movement).
        class GamepadInput {
          public:
            /// Used to separate an axis in two inputs. Needed for movements (left/right).
            enum class AxisDirection {
                None,     //< Invalid
                Negative, //< Negative value ([-1, 0])
                Positive, //< Positive range ([0, 1])
            };

            /// Construct a new GamepadInput from a simple button.
            /// @warning Setting UNKNOWN button will result in a undefined behavior for latter usage.
            ///
            /// @param button button to check.
            GamepadInput(raylib::core::Gamepad::Button button = raylib::core::Gamepad::Button::UNKNOWN);

            /// Construct a new GamepadInput from an axis direction.
            ///
            /// @param axis axis to check.
            /// @param direction direction to check.
            GamepadInput(raylib::core::Gamepad::Axis axis, AxisDirection direction);

            /// Construct a copy of a GamepadInput object.
            ///
            /// @param other object to copy.
            ///
            GamepadInput(const GamepadInput &other) = default;

            /// Destroys the GamepadInput.
            ~GamepadInput() = default;

            /// Copy a GamepadInput object.
            ///
            /// @param other object to copy.
            /// @return GamepadInput& @b this.
            ///
            GamepadInput &operator=(const GamepadInput &other) = default;

            /// Get the Button stored.
            ///
            /// @return raylib::core::Gamepad::Button button stored.
            raylib::core::Gamepad::Button getButton() const;

            /// Get the axis stored.
            ///
            /// @return raylib::core::Gamepad::Axis axis stored.
            raylib::core::Gamepad::Axis getAxis() const;

            /// Get the axis direction.
            ///
            /// @return AxisDirection axis direction stored.
            AxisDirection getAxisDirection() const;

            /// Test if the input stored is a button.
            ///
            /// @retval true when the input stored is a valid button.
            /// @retval false when the input stored is an axis direction.
            bool isButton() const;

            /// Convert the input to string for settings saving in files.
            ///
            /// @note The format for button inputs are "[button]" where [button] is replaced by the integral value of
            /// the Gamepad::Button enum.
            /// @note The format for axis direction are "[axis]:[direction]" where [axis] is replaced by the integral
            /// value of the Gamepad::Axis enum and [direction] is replaced with the integral value of the AxisDirection
            /// enum. value
            ///
            /// @return std::string string representation of @b this.
            std::string toString() const;

            /// Lower than comparison operator overload.
            ///
            /// @note This overload is required to store @ref GamepadInput objects as key in @ref std::map.
            /// @note It doesn't make sense to test if an input is lower than an other except for sorting.
            ///
            /// @param other object to compare with.
            /// @retval true If @b this is considered lower than @c other.
            /// @retval false Otherwise.
            bool operator<(const GamepadInput &other) const;

            /// Equality comparison operator overload.
            ///
            /// @param other object to compare with.
            /// @retval true If @b this and @c other are equals.
            /// @retval false otherwise.
            bool operator==(const GamepadInput &other) const;

          private:
            raylib::core::Gamepad::Button _button;
            raylib::core::Gamepad::Axis _axis;
            AxisDirection _axisDirection;
        };
    } // namespace settings
} // namespace game

#endif /* !GAME_SETTINGS_GAMEPADINPUT_HPP_ */
