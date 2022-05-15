/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Cursor
*/

#include "Cursor.hpp"

raylib::Core::Cursor::Cursor()
{
}

raylib::Core::Cursor::~Cursor()
{
}

void raylib::Core::Cursor::showCursor(void)
{
    ShowCursor();
}

void raylib::Core::Cursor::hideCursor(void)
{
    HideCursor();
}

bool raylib::Core::Cursor::isCursorHidden(void)
{
    return IsCursorHidden();
}

void raylib::Core::Cursor::enableCursor(void)
{
    EnableCursor();
}

void raylib::Core::Cursor::disableCursor(void)
{
    DisableCursor();
}

bool raylib::Core::Cursor::isCursorOnScreen(void)
{
    return IsCursorOnScreen();
}
