/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mouse
*/

#ifndef MOUSE_HPP_
#define MOUSE_HPP_

#include "Vector2.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        class Mouse {
          public:
            /// Constructor of the Mouse
            Mouse();

            /// Destructor of the Mouse
            ~Mouse();

            /// A wrapper function for the raylib function IsMouseButtonPressed.
            ///
            ///@param button The button to check.
            ///
            ///@return A boolean value.
            bool isMouseButtonPressed(int button);

            /// It returns a bool value.
            ///
            ///@param button The button to check.
            ///
            ///@return A boolean value.
            bool isMouseButtonDown(int button);

            /// A wrapper for the raylib function of the same name.
            ///
            ///@param button The mouse button to check.
            ///
            ///@return A boolean value.
            bool isMouseButtonReleased(int button);

            /// It returns true if the mouse button is up.
            ///
            ///@param button The button to check.
            ///
            ///@return A boolean value.
            bool isMouseButtonUp(int button);

            /// It returns the mouse's x position.
            ///
            ///@return The mouse's x position.
            int getMouseX(void);

            /// It returns the mouse's y position.
            ///
            ///@return The mouse's y position.
            int getMouseY(void);

            /// It returns the mouse position.
            ///
            ///@return A Vector2 object.
            Vector2 getMousePosition(void);

            /// It returns the mouse delta.
            ///
            ///@return A Vector2 object.
            Vector2 getMouseDelta(void);

            /// Sets the mouse position
            ///
            ///@param x The x position of the mouse
            ///@param y The y position of the mouse.
            void setMousePosition(int x, int y);

            /// Sets the mouse offset
            ///
            ///@param offsetX The X offset of the mouse.
            ///@param offsetY The Y offset of the mouse.
            void setMouseOffset(int offsetX, int offsetY);

            /// Sets mouse scaling
            ///
            ///@param scaleX Horizontal mouse scaling factor
            ///@param scaleY Vertical scaling factor for mouse input
            void setMouseScale(float scaleX, float scaleY);

            /// It returns the mouse wheel movement Y.
            ///
            /// @return The mouse wheel movement.
            float getMouseWheelMove(void);

            /// Sets the mouse cursor icon
            /// @param cursor The cursor to set.
            void setMouseCursor(int cursor);

          protected:
          private:
        };
    } // namespace core
} // namespace raylib

#endif /* !MOUSE_HPP_ */
