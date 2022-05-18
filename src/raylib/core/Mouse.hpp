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
                /// A wrapper function for the raylib function IsMouseButtonPressed.
                ///
                ///@param button The button to check.
                ///
                ///@return A boolean value.
                bool isButtonPressed(int button);

                /// It returns a bool value.
                ///
                ///@param button The button to check.
                ///
                ///@return A boolean value.
                bool isButtonDown(int button);

                /// A wrapper for the raylib function of the same name.
                ///
                ///@param button The mouse button to check.
                ///
                ///@return A boolean value.
                bool isButtonReleased(int button);

                /// It returns true if the mouse button is up.
                ///
                ///@param button The button to check.
                ///
                ///@return A boolean value.
                bool isButtonUp(int button);

                /// It returns the mouse's x position.
                ///
                ///@return The mouse's x position.
                int getX(void);

                /// It returns the mouse's y position.
                ///
                ///@return The mouse's y position.
                int getY(void);

                /// It returns the mouse position.
                ///
                ///@return A Vector2 object.
                Vector2 getPosition(void);

                /// It returns the mouse delta.
                ///
                ///@return A Vector2 object.
                Vector2 getDelta(void);

                /// Sets the mouse position
                ///
                ///@param x The x position of the mouse
                ///@param y The y position of the mouse.
                void setPosition(int x, int y);

                /// Sets the mouse offset
                ///
                ///@param offsetX The X offset of the mouse.
                ///@param offsetY The Y offset of the mouse.
                void setOffset(int offsetX, int offsetY);

                /// Sets mouse scaling
                ///
                ///@param scaleX Horizontal mouse scaling factor
                ///@param scaleY Vertical scaling factor for mouse input
                void setScale(float scaleX, float scaleY);

                /// It returns the mouse wheel movement Y.
                ///
                /// @return The mouse wheel movement.
                float getWheelMove(void);

                /// Sets the mouse cursor icon
                /// @param cursor The cursor to set.
                void setCursor(int cursor);

        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_MOUSE_HPP_ */
