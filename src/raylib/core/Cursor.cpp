/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Cursor
*/

#include "Cursor.hpp"

namespace raylib
{
    namespace core
    {
        void Cursor::show(void) { ShowCursor(); }

        void Cursor::hide(void) { HideCursor(); }

        bool Cursor::isHidden(void) { return IsCursorHidden(); }

        void Cursor::enable(void) { EnableCursor(); }

        void Cursor::disable(void) { DisableCursor(); }

        bool Cursor::isOnScreen(void) { return IsCursorOnScreen(); }
    } // namespace core
} // namespace raylib
