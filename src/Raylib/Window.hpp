/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

namespace raylib {

class Window {
    public:
        static Window& getInstance();
        Window(const Window&) = delete;
        Window &operator=(const Window&) = delete;
        Window(const Window&) = delete;
        Window &operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window &operator=(Window&&) = delete;
        ~Window();
        void open(int width = 1920, int height = 1080, const char *title = "BM:GO");
        void close();
        void clear();
        bool windowShouldClose();
        void setTargetFPS(int fps);
        void drawFPS(int x, int y);
        void beginDrawing();
        void endDrawing();

    private:
        Window() {}
};

}

#endif /* WINDOW_HPP_ */
