/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#include "Window.hpp"

extern "C" {
    #include "raylib.h"
}

raylib::Core::Window &raylib::Core::Window::getInstance()
{
    static Window instance;

    return instance;
}

raylib::Core::Window::~Window()
{
}

void raylib::Core::Window::open(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void raylib::Core::Window::close()
{
    CloseWindow();
}

void raylib::Core::Window::clear()
{
    ClearBackground(BLACK);
}

bool raylib::Core::Window::windowShouldClose()
{
    return WindowShouldClose();
}

void raylib::Core::Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

void raylib::Core::Window::drawFPS(int x, int y)
{
    DrawFPS(x, y);
}

void raylib::Core::Window::beginDrawing()
{
    BeginDrawing();
}

void raylib::Core::Window::endDrawing()
{
    EndDrawing();
}
