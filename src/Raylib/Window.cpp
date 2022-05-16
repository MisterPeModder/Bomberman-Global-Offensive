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

void raylib::Window::open(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void raylib::Window::close()
{
    CloseWindow();
}

void raylib::Window::clear()
{
    ClearBackground(BLACK);
}

bool raylib::Window::windowShouldClose()
{
    return WindowShouldClose();
}

void raylib::Window::setTargetFPS(int fps)
{
    SetTargetFPS(fps);
}

void raylib::Window::drawFPS(int x, int y)
{
    DrawFPS(x, y);
}

void raylib::Window::beginDrawing()
{
    BeginDrawing();
}

void raylib::Window::endDrawing()
{
    EndDrawing();
}
