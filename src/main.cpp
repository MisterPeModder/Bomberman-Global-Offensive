#include <iostream>
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"

#include "raylib/shapes/Cylinder.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

constexpr int WIDTH(500);
constexpr int HEIGHT(500);

static void drawFrame(void *arg)
{
    raylib::core::Camera3D *camera = reinterpret_cast<raylib::core::Camera3D *>(arg);

    raylib::core::Window::beginDrawing();
    raylib::core::Window::clear();
    camera->begin3D();
    camera->end3D();

    DrawText("<insert great game here>", WIDTH / 2 - 120, HEIGHT / 2 - 1, 20, LIGHTGRAY);
    raylib::core::Window::endDrawing();
    raylib::core::Window::drawFPS(10, 10);
}

int main()
{
    raylib::core::Camera3D camera;
    // Setup the logger parameters
    Logger::logger.setOutputFile("log.txt");
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);

    /// Setup the locales parameters
    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << localization::Ressources::rsHello << std::endl;

    // Basic placeholder window
    raylib::core::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, &camera, 0, 1);
#else
    raylib::core::Window::setTargetFPS(60);

    while (!WindowShouldClose())
        drawFrame(&camera);
#endif

    CloseWindow();
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
