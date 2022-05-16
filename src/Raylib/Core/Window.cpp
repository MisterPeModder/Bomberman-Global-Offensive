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

        Window &Window::getInstance()
        {
            static Window instance;

            return instance;
        }

        Window::~Window() {}

        void Window::open(float width, float height, const char *title) { InitWindow(width, height, title); }

        void Window::close() { CloseWindow(); }

        void Window::clear() { ClearBackground(BLACK); }

        bool Window::windowShouldClose() { return WindowShouldClose(); }

        void Window::setTargetFPS(float fps) { SetTargetFPS(fps); }

        void Window::drawFPS(float x, float y) { DrawFPS(x, y); }

        void Window::beginDrawing() { BeginDrawing(); }

        void Window::endDrawing() { EndDrawing(); }
    } // namespace core
} // namespace raylib
