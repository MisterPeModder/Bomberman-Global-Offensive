/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Window
*/

#include "Window.hpp"
#include "logger/Logger.hpp"
#include "raylib/textures/Image.hpp"

extern "C"
{
#include "raylib.h"
}

#include <algorithm>

namespace raylib
{
    namespace core
    {
        void Window::open(int width, int height, std::string_view title)
        {
            InitWindow(width, height, title.data());
            SetWindowMinSize(1280, 720);
        }

        bool Window::_shouldClose = false;

        void Window::close() { CloseWindow(); }

        void Window::clear(const Color &color) { ClearBackground(color.asRaylib()); }

        bool Window::getShouldClose() { return _shouldClose || WindowShouldClose(); }

        void Window::setShouldClose() { _shouldClose = true; }

        void Window::setTargetFPS(int fps) { SetTargetFPS(fps); }

        void Window::drawFPS(int x, int y) { DrawFPS(x, y); }

        void Window::beginDrawing() { BeginDrawing(); }

        void Window::endDrawing() { EndDrawing(); }

        void Window::setSize(int width, int height)
        {
            Logger::logger.log(
                Logger::Severity::Information, [=](auto &out) { out << "Resized to " << width << 'x' << height; });
            SetWindowSize(std::max(0, width), std::max(0, height));
        }

        int Window::getWidth() { return GetScreenWidth(); }

        int Window::getHeight() { return GetScreenHeight(); }

        void Window::toggleFullscreen() { ToggleFullscreen(); }

        bool Window::isFullscreen() { return IsWindowFullscreen(); }

        void Window::setIcon(textures::Image const &icon) { SetWindowIcon(icon.asRaylib()); }

        std::string_view Window::getClipboard()
        {
            char const *text = ::GetClipboardText();

            if (text == nullptr)
                return {};
            return text;
        }

        void Window::setClipboard(std::string_view text) { ::SetClipboardText(text.data()); }

    } // namespace core
} // namespace raylib
