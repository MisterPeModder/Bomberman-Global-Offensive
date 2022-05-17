/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

/// Raylib namespace
namespace raylib
{
    /// Core namespace (inside of raylib)
    namespace core
    {
        /// The window static class that will manage the raylib window
        class Window {
            public:
                /// Open the window (may cause problems if the window is already open)
                ///
                /// @param width The width of the window
                /// @param height The height of the window
                /// @param title The title of the window
                static void open(int width = 1920, int height = 1080, const char *title = "BM:GO");
                /// Close the window
                static void close();
                /// Clear the window with a black background
                static void clear();
                /// Returns if the window should close or not (when a close window event is received for example)
                ///
                /// @retval true if the window should close
                /// @retval false if the window should not close
                static bool windowShouldClose();
                /// Set the max FPS the game should run at
                ///
                /// @param fps The frames per second the game should run at
                static void setTargetFPS(int fps);
                /// Displays the number of frames per seconds of the game on screen
                ///
                /// @param x The X position where the number of FPS will be displayed
                /// @param y The Y position where the number of FPS will be displayed
                static void drawFPS(int x, int y);
                /// Allow the draw functions to work
                static void beginDrawing();
                /// Block the draw functions
                static void endDrawing();
        };
    } // namespace core
} // namespace raylib

#endif /* WINDOW_HPP_ */
