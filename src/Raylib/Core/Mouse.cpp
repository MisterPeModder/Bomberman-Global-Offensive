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

        Mouse::Mouse() {}

        Mouse::~Mouse() {}

        bool Mouse::isMouseButtonPressed(int button) { return IsMouseButtonPressed(button); }

        bool Mouse::isMouseButtonDown(int button) { return IsMouseButtonDown(button); }

        bool Mouse::isMouseButtonReleased(int button) { return IsMouseButtonReleased(button); }

        bool Mouse::isMouseButtonUp(int button) { return IsMouseButtonUp(button); }

        int Mouse::getMouseX(void) { return GetMouseX(); }

        int Mouse::getMouseY(void) { return GetMouseY(); }

        Vector2 Mouse::getMousePosition(void) { return GetMousePosition(); }

        Vector2 Mouse::getMouseDelta(void) { return GetMouseDelta(); }

        void Mouse::setMousePosition(int x, int y) { SetMousePosition(x, y); }

        void Mouse::setMouseOffset(int offsetX, int offsetY) { SetMouseOffset(offsetX, offsetY); }

        void Mouse::setMouseScale(float scaleX, float scaleY) { SetMouseScale(scaleX, scaleY); }

        float Mouse::getMouseWheelMove(void) { return GetMouseWheelMove(); }

        void Mouse::setMouseCursor(int cursor) { SetMouseCursor(cursor); }
    } // namespace core
} // namespace raylib
