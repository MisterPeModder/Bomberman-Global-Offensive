/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Cursor
*/

#ifndef RAYLIB_CORE_CURSOR_HPP_
#define RAYLIB_CORE_CURSOR_HPP_

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        class Cursor {
          public:
            /// Constructor of the Cursor
            Cursor();

            /// Destructor of the Cursor
            ~Cursor();

            /// It shows the cursor
            void showCursor(void);

            /// It hides the cursor.
            void hideCursor(void);

            /// It returns a boolean value.
            ///
            /// @return A boolean value.
            bool isCursorHidden(void);

            /// It enables the cursor.
            void enableCursor(void);

            /// It disables the cursor.
            void disableCursor(void);

            /// It returns true if the cursor is on the screen.
            ///
            /// @return A boolean value.
            bool isCursorOnScreen(void);

          protected:
          private:
        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_CURSOR_HPP_ */
