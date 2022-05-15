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
    return isMouseButtonPressed(button);
}

bool raylib::Core::Mouse::isMouseButtonDown(int button)
{
    return isMouseButtonDown(button);
}

bool raylib::Core::Mouse::isMouseButtonReleased(int button)
{
    return isMouseButtonReleased(button);
}

bool raylib::Core::Mouse::isMouseButtonUp(int button)
{
    return isMouseButtonUp(button);
}

int raylib::Core::Mouse::getMouseX(void)
{
    return getMouseX();
}

int raylib::Core::Mouse::getMouseY(void)
{
    return getMouseY();
}

raylib::Core::Vector2 raylib::Core::Mouse::getMousePosition(void)
{
    return getMousePosition();
}

raylib::Core::Vector2 raylib::Core::Mouse::getMouseDelta(void)
{
    return getMouseDelta();
}

void raylib::Core::Mouse::setMousePosition(int x, int y)
{
    setMousePosition(x, y);
}

void raylib::Core::Mouse::setMouseOffset(int offsetX, int offsetY)
{
    setMouseOffset(offsetX, offsetY);
}

void raylib::Core::Mouse::setMouseScale(float scaleX, float scaleY)
{
    setMouseScale(scaleX, scaleY);
}

float raylib::Core::Mouse::getMouseWheelMove(void)
{
    return getMouseWheelMove();
}

void raylib::Core::Mouse::setMouseCursor(int cursor)
{
    setMouseCursor(cursor);
}
