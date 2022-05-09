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

    protected:
    private:
};

}
