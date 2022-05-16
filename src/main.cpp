#include <iostream>
#include "Raylib/Camera3D.hpp"
#include "Raylib/Window.hpp"

// int main()
// {
//     raylib::Camera3D camera;

//     raylib::Window::setTargetFPS(60);
//     raylib::Window::open(1200, 800, "hell oworld");

//     while (!raylib::Window::windowShouldClose()) {
//         raylib::Window::beginDrawing();

//         raylib::Window::clear();
//         camera.begin3D();

//         // draw cube

//         camera.end3D();
//         raylib::Window::drawFPS(10, 10);

//         raylib::Window::endDrawing();
//     }
//     raylib::Window::close();
#include "logger/Logger.hpp"

#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

constexpr int WIDTH(500);
constexpr int HEIGHT(500);

static void drawFrame(void *arg)
{
    raylib::Camera3D *camera = reinterpret_cast<raylib::Camera3D *>(arg);

    raylib::Window::beginDrawing();
    raylib::Window::clear();
    DrawText("<insert great game here>", WIDTH / 2 - 120, HEIGHT / 2 - 1, 20, LIGHTGRAY);
    raylib::Window::endDrawing();
    raylib::Window::drawFPS(10, 10);
}

int main()
{
    raylib::Camera3D camera;
    // Setup the logger parameters
    Logger::logger.setOutputFile("log.txt");
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << "Hello, World!" << std::endl;
    Logger::logger.log(Logger::Severity::Information, "End of program");

    // Basic placeholder window
    raylib::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, &camera, 0, 1);
#else
    raylib::Window::setTargetFPS(60);

    while (!WindowShouldClose())
        drawFrame(&camera);
#endif

    raylib::Window::close();

    return 0;
}
