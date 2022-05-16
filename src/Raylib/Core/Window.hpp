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
            static Window &getInstance();
            Window(Window &&) = delete;
            Window &operator=(Window &&) = delete;
            ~Window();
            void open(float width = 1920, float height = 1080, const char *title = "BM:GO");
            void close();
            void clear();
            bool windowShouldClose();
            void setTargetFPS(float fps);
            void drawFPS(float x, float y);
            void beginDrawing();
            void endDrawing();

          private:
            explicit Window() {}
            explicit Window(const Window &);
            Window &operator=(const Window &);
        };
    } // namespace core
} // namespace raylib

#endif /* WINDOW_HPP_ */
