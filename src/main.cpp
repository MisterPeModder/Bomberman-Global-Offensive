#include <iostream>
#include "Raylib/Camera3D.hpp"
#include "Raylib/Window.hpp"
#include <unistd.h>

int main()
{
    raylib::Camera3D camera;

    raylib::Window::setTargetFPS(60);
    raylib::Window::open(1200, 800, "hell oworld");

    while (!raylib::Window::windowShouldClose()) {
        raylib::Window::beginDrawing();

        raylib::Window::clear();
        camera.begin3D();

        // draw cube

        camera.end3D();
        raylib::Window::drawFPS(10, 10);

        raylib::Window::endDrawing();
    }
    raylib::Window::close();
}
