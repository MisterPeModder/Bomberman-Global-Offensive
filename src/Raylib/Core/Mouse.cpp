/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mouse
*/

#include "Mouse.hpp"

raylib::Core::Mouse::Mouse()
{
}

raylib::Core::Mouse::~Mouse()
{
}

bool raylib::Core::Mouse::isMouseButtonPressed(int button)
{
    return IsMouseButtonPressed(button);
}

bool raylib::Core::Mouse::isMouseButtonDown(int button)
{
    return IsMouseButtonDown(button);
}

bool raylib::Core::Mouse::isMouseButtonReleased(int button)
{
    return IsMouseButtonReleased(button);
}

bool raylib::Core::Mouse::isMouseButtonUp(int button)
{
    return IsMouseButtonUp(button);
}

int raylib::Core::Mouse::getMouseX(void)
{
    return GetMouseX();
}

int raylib::Core::Mouse::getMouseY(void)
{
    return GetMouseY();
}

raylib::Core::Vector2 raylib::Core::Mouse::getMousePosition(void)
{
    return GetMousePosition();
}

raylib::Core::Vector2 raylib::Core::Mouse::getMouseDelta(void)
{
    return GetMouseDelta();
}

void raylib::Core::Mouse::setMousePosition(int x, int y)
{
    SetMousePosition(x, y);
}

void raylib::Core::Mouse::setMouseOffset(int offsetX, int offsetY)
{
    SetMouseOffset(offsetX, offsetY);
}

void raylib::Core::Mouse::setMouseScale(float scaleX, float scaleY)
{
    SetMouseScale(scaleX, scaleY);
}

float raylib::Core::Mouse::getMouseWheelMove(void)
{
    return GetMouseWheelMove();
}

void raylib::Core::Mouse::setMouseCursor(int cursor)
{
    SetMouseCursor(cursor);
}
