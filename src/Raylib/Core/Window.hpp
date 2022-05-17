/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

namespace raylib
{

    namespace core
    {

        class Window {
            public:
              static void open(int width = 1920, int height = 1080, const char *title = "BM:GO");
              static void close();
              static void clear();
              static bool windowShouldClose();
              static void setTargetFPS(int fps);
              static void drawFPS(int x, int y);
              static void beginDrawing();
              static void endDrawing();
        };
    } // namespace core
} // namespace raylib

#endif /* WINDOW_HPP_ */
