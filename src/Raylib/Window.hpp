/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#pragma once

namespace raylib {

class Window {
    public:
        Window();
        ~Window();
        void open(int width, int height, const char *title);
        void close();
        void clear();
        bool windowShouldClose();
        void setTargetFPS(int fps);
        void drawFPS(int x, int y);
        void beginDrawing();
        void endDrawing();

    protected:
    private:
};

}
