#include <iostream>
#include "Raylib/Camera3D.hpp"
#include "Raylib/Window.hpp"
#include <unistd.h>

int main()
{
    raylib::Window& window = raylib::Window::getInstance();
    raylib::Camera3D camera;

    window.setTargetFPS(60);
    window.open(1200, 800, "hell oworld");

    while (!window.windowShouldClose()) {
        window.beginDrawing();

        window.clear();
        camera.begin3D();

        // draw cube

        camera.end3D();
        window.drawFPS(10, 10);

        window.endDrawing();
    }
    window.close();
}
