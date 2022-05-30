/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#include "Window.hpp"

extern "C"
{
#include "raylib.h"
}

namespace raylib
{
    namespace core
    {
        void Window::open(int width, int height, std::string_view title) { InitWindow(width, height, title.data()); }

        void Window::close() { CloseWindow(); }

        void Window::clear(const Color &color) { ClearBackground(color.asRaylib()); }

        bool Window::windowShouldClose() { return WindowShouldClose(); }

        void Window::setTargetFPS(int fps) { SetTargetFPS(fps); }

        void Window::drawFPS(int x, int y) { DrawFPS(x, y); }

        void Window::beginDrawing() { BeginDrawing(); }

        void Window::endDrawing() { EndDrawing(); }

    } // namespace core
} // namespace raylib
