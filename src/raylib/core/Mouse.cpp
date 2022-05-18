/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Mouse
*/

#include "Mouse.hpp"

namespace raylib
{
    namespace core
    {
        bool Mouse::isButtonPressed(int button) { return IsMouseButtonPressed(button); }

        bool Mouse::isButtonDown(int button) { return IsMouseButtonDown(button); }

        bool Mouse::isButtonReleased(int button) { return IsMouseButtonReleased(button); }

        bool Mouse::isButtonUp(int button) { return IsMouseButtonUp(button); }

        int Mouse::getX(void) { return GetMouseX(); }

        int Mouse::getY(void) { return GetMouseY(); }

        Vector2 Mouse::getPosition(void) { return GetMousePosition(); }

        Vector2 Mouse::getDelta(void) { return GetMouseDelta(); }

        void Mouse::setPosition(int x, int y) { SetMousePosition(x, y); }

        void Mouse::setOffset(int offsetX, int offsetY) { SetMouseOffset(offsetX, offsetY); }

        void Mouse::setScale(float scaleX, float scaleY) { SetMouseScale(scaleX, scaleY); }

        float Mouse::getWheelMove(void) { return GetMouseWheelMove(); }

        void Mouse::setCursor(int cursor) { SetMouseCursor(cursor); }
    } // namespace core
} // namespace raylib
