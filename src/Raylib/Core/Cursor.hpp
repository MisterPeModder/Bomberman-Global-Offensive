/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Cursor
*/

#ifndef CURSOR_HPP_
#define CURSOR_HPP_

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
            /// @brief Constructor of the Cursor
            Cursor();

            /// @brief Destructor of the Cursor
            ~Cursor();

            /// @brief It shows the cursor
            void showCursor(void);

            /// @brief It hides the cursor.
            void hideCursor(void);

            /// @brief It returns a boolean value.
            ///
            /// @return A boolean value.
            bool isCursorHidden(void);

            /// @brief It enables the cursor.
            void enableCursor(void);

            /// @brief It disables the cursor.
            void disableCursor(void);

            /// @brief It returns true if the cursor is on the screen.
            ///
            /// @return A boolean value.
            bool isCursorOnScreen(void);

          protected:
          private:
        };
    } // namespace core
} // namespace raylib

#endif /* !CURSOR_HPP_ */
