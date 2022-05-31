/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Gamepad
*/

#ifndef RAYLIB_CORE_GAMEPAD_HPP_
#define RAYLIB_CORE_GAMEPAD_HPP_

#include "Vector2.hpp"
#include <string_view>

extern "C"
{
#include <raylib.h>
}

namespace raylib
{
    namespace core
    {
        class Gamepad {
          public:
            /// Gamepad buttons
            enum class Button {
                UNKNOWN = 0, // Unknown button, just for error checking
                /// D-Pad
                DPAD_FACE_UP,    // Gamepad left DPAD up button
                DPAD_FACE_RIGHT, // Gamepad left DPAD right button
                DPAD_FACE_DOWN,  // Gamepad left DPAD down button
                DPAD_FACE_LEFT,  // Gamepad left DPAD left button
                /// Face Buttons
                FACE_UP,    // Gamepad right button up (i.e. PS3: Triangle, Xbox: Y)
                FACE_RIGHT, // Gamepad right button right (i.e. PS3: Square, Xbox: X)
                FACE_DOWN,  // Gamepad right button down (i.e. PS3: Cross, Xbox: A)
                FACE_LEFT,  // Gamepad right button left (i.e. PS3: Circle, Xbox: B)
                /// Backward buttons
                LEFT_BUMPER,   // Gamepad left bumper
                LEFT_TRIGGER,  // Gamepad left trigger
                RIGHT_BUMPER,  // Gamepad right bumper
                RIGHT_TRIGGER, // Gamepad right trigger
                /// Middle buttons
                MIDDLE_LEFT,  // Gamepad center buttons, left one (i.e. PS3: Select, Xbox: back)
                MIDDLE,       // Gamepad center buttons, middle one (i.e. PS3: PS, Xbox: XBOX)
                MIDDLE_RIGHT, // Gamepad center buttons, right one (i.e. PS3: Start, Xbox: Start)
                /// Joystick buttons
                LEFT_THUMB, // Gamepad joystick pressed button left
                RIGHT_THUMB // Gamepad joystick pressed button right
            };

            /// Gamepad axis, all in range [-1, 1]
            enum class Axis {
                LEFT_X = 0,       // Gamepad left joystick X axis, default value is 0
                LEFT_Y = 1,       // Gamepad left joystick Y axis, default value is 0
                RIGHT_X = 2,      // Gamepad right joystick X axis, default value is 0
                RIGHT_Y = 3,      // Gamepad right joystick Y axis, default value is 0
                LEFT_TRIGGER = 4, // Gamepad back trigger left, default value is -1
                RIGHT_TRIGGER = 5 // Gamepad back trigger right, default value is -1
            };

            /// Gamepad joysticks (two axis combined)
            enum class Joystick {
                LEFT,  // Left joystick
                RIGHT, // Right joystick
            };

            /// Construct a new Gamepad object.
            ///
            /// @param id id of the gamepad.
            Gamepad(int id = 0);

            /// Default copy constructor.
            ///
            /// @param other gamepad to copy.
            Gamepad(const Gamepad &other) = default;

            /// Destroy the gamepad object.
            ~Gamepad() = default;

            /// Default assignement operator.
            ///
            /// @param other gamepad to copy.
            /// @return Gamepad& @b this.
            Gamepad &operator=(const Gamepad &other) = default;

            /// Assignement operator with a new gamepad ID.
            /// @note The Gamepad class only store the id of the gamepad, and can be considered as an int.
            ///
            /// @return Gamepad& @b this.
            Gamepad &operator=(int id);

            /// Check if a gamepad is available.
            ///
            /// @return true If the gamepad is available.
            bool isAvailable() const;

            /// Get gamepad internal name id.
            ///
            /// @return internal name.
            std::string_view getName() const;

            /// Check if a gamepad button has been pressed once.
            ///
            /// @param button button to check.
            /// @return true If the button has been pressed.
            bool isButtonPressed(Button button) const;

            /// Check if a gamepad button is being pressed.
            ///
            ///  @param button button to check.
            ///  @return true If the button is down.
            bool isButtonDown(Button button) const;

            /// Check if a gamepad button has been released once.
            ///
            /// @param button button to check.
            /// @return true If the button has been released.
            bool isButtonReleased(Button button) const;

            /// Check if a gamepad button is NOT being pressed.
            ///
            /// @param button button to check.
            /// @return true If the button is not pressed.
            bool isButtonUp(Button button) const;

            /// Get the last gamepad button pressed.
            ///
            /// @return Button last button pressed.
            static Button getButtonPressed();

            /// Get the number of axis of the gamepad.
            ///
            /// @return int number of axis of the gamepad.
            int getAxisCount() const;

            /// Get the movement of an axis.
            ///
            /// @param axis axis to check.
            /// @return float movement of the axis.
            float getAxisMovement(Axis axis) const;

            /// Get the movement of the two axis of a joystick.
            ///
            /// @param joystick joystick to check.
            /// @return Vector2 direction of the joystick (x, y) in range [-1, 1].
            Vector2 getJoystickDirection(Joystick joystick) const;

            /// Set internal gamepad mappings (SDL_GameControllerDB)
            ///
            /// @param mappings new mapping to apply
            /// @return int maybe 0 on succeed and -1 on failure, didn't found it in the raylib documentation
            int setMappings(std::string_view mappings) const;

          private:
            int _id;
        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_GAMEPAD_HPP_ */
