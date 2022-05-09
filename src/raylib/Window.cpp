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

raylib::Window::Window()
{
}

raylib::Window::~Window()
{
}

void raylib::Window::open(int width, int height, const char *title)
{
    InitWindow(width, height, title);
}

void raylib::Window::close(void)
{
    CloseWindow();
}
