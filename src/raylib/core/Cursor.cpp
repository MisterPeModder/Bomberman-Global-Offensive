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

        Cursor::Cursor() {}

        Cursor::~Cursor() {}

        void Cursor::showCursor(void) { ShowCursor(); }

        void Cursor::hideCursor(void) { HideCursor(); }

        bool Cursor::isCursorHidden(void) { return IsCursorHidden(); }

        void Cursor::enableCursor(void) { EnableCursor(); }

        void Cursor::disableCursor(void) { DisableCursor(); }

        bool Cursor::isCursorOnScreen(void) { return IsCursorOnScreen(); }
    } // namespace core
} // namespace raylib
