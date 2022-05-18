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
        /// The cursor static class that will manage the raylib cursor
        class Cursor {
            public:
                /// Makes the mouse cursor visible
                static void show(void);

                /// Makes the mouse cursor invisible
                static void hide(void);

                /// Returns if the cursor is hidden or not
                ///
                /// @retval true if the curser is hidden
                /// @retval false if the curser is not hidden
                static bool isHidden(void);

                /// Enables the cursor
                static void enable(void);

                /// Disables the cursor
                static void disable(void);

                /// Returns if the cursor is on screen or not
                ///
                /// @retval true if the cursor is on screen
                /// @retval false if the cursor is not on screen
                static bool isOnScreen(void);

        };
    } // namespace core
} // namespace raylib

#endif /* !RAYLIB_CORE_CURSOR_HPP_ */
