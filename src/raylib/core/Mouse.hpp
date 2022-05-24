/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mouse
*/

#ifndef RAYLIB_CORE_MOUSE_HPP_
#define RAYLIB_CORE_MOUSE_HPP_

#include "Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        /// The mouse static class that will manage the raylib mouse
        class Mouse {
          public:
            /// Gets if the button specified in argument has been pressed once or not
            ///
            /// @param button the button to check
            ///
            /// @return true if the button is pressed or false otherwise
            static constexpr bool isButtonPressed(int button) { return IsMouseButtonPressed(button); }

            /// Gets if the button specified in argument is currently being pressed or not
            ///
            /// @param button the button to check
            ///
            /// @return true if the button is pressed or false otherwise
            static constexpr bool isButtonDown(int button) { return IsMouseButtonDown(button); }

            /// Gets if the button specified in argument has been released once or not
            ///
            /// @param button the button to check
            ///
            /// @return true if the button is pressed or false otherwise
            static constexpr bool isButtonReleased(int button) { return IsMouseButtonReleased(button); }

            /// Gets if the button specified in argument is currently not being pressed or not
            ///
            /// @param button the button to check
            ///
            /// @return true if the button is not being pressed or false otherwise
            static constexpr bool isButtonUp(int button) { return IsMouseButtonUp(button); }

            /// Gets the mouse's x position.
            ///
            /// @return The mouse's x position.
            static constexpr int getX() { return GetMouseX(); }

            /// Gets the mouse's y position.
            ///
            /// @return The mouse's y position.
            static constexpr int getY() { return GetMouseY(); }

            /// Gets the mouse position.
            ///
            /// @return The mouse position.
            static inline Vector2 getPosition() { return GetMousePosition(); }

            /// Gets the mouse delta.
            ///
            /// @return The mouse delta.
            static inline Vector2 getDelta() { return GetMouseDelta(); }

            /// Sets the mouse position
            ///
            /// @param x The new x position of the mouse
            /// @param y The new y position of the mouse
            static constexpr void setPosition(float x, float y) { SetMousePosition(static_cast<int>(x), static_cast<int>(y)); }

            /// Sets the mouse position
            ///
            /// @param x The new x position of the mouse
            /// @param y The new y position of the mouse
            static constexpr void setPosition(Vector2 &pos) { SetMousePosition(static_cast<int>(pos.getX()), static_cast<int>(pos.getY())); }

            /// Sets the mouse offset
            ///
            /// @param offsetX The X offset of the mouse.
            /// @param offsetY The Y offset of the mouse.
            static constexpr void setOffset(float offsetX, float offsetY)  { SetMouseOffset(static_cast<int>(offsetX), static_cast<int>(offsetY)); }
            /// Sets the mouse offset
            ///
            /// @param offsetX The X offset of the mouse.
            /// @param offsetY The Y offset of the mouse.
            static constexpr void setOffset(Vector2 &offset)  { SetMouseOffset(static_cast<int>(offset.getX()), static_cast<int>(offset.getY())); }

            /// Sets mouse scaling
            ///
            /// @param scaleX Horizontal mouse scaling factor
            /// @param scaleY Vertical scaling factor for mouse input
            static constexpr void setScale(float scaleX, float scaleY) { SetMouseScale(scaleX, scaleY); }

            /// Gets the mouse wheel Y movement.
            ///
            /// @return The mouse wheel movement.
            static constexpr float getWheelMove() { return GetMouseWheelMove(); }

            /// Sets the mouse cursor
            ///
            /// @param cursor The cursor to set.
            static constexpr void setCursor(int cursor) { SetMouseCursor(cursor); }

        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_MOUSE_HPP_ */
