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
        explicit Window() {}
        explicit Window(const Window&) = default;
        Window &operator=(const Window&) = default;
        Window(Window&&) = default;
        Window &operator=(Window&&) = default;
        static Window instance;
};

}

#endif /* WINDOW_HPP_ */
