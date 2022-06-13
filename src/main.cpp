/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** main
*/

#include <filesystem>
#include <iostream>
#include <memory>

#include "ecs/World.hpp"
#include "localization/Localization.hpp"
#include "localization/Resources.hpp"
#include "logger/Logger.hpp"
#include "menu/MainMenu.hpp"

#include "game/gui/components/Widget.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/raylib.hpp"
#include "script/Engine.hpp"

#include "game/Game.hpp"

#include "menu/MainMenu.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

constexpr int WIDTH(1080);
constexpr int HEIGHT(720);

struct Params {
    ecs::World world;
    raylib::core::Camera3D camera;
    game::Game game;

    Params() : world(), camera(), game(this->world, game::Game::Parameters(1)) {}
};

static void drawFrame(void *args)
{
    Params *params = reinterpret_cast<Params *>(args);

    params->camera.update();
    params->game.drawFrame(params->camera);
}

static void setupLogger()
{
    // Setup the logger parameters
    Logger::logger.setLogLevel(Logger::Severity::Debug);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);
    Logger::logger.setName("main");
    raylib::initLogger(LOG_INFO);
    Logger::logger.log(Logger::Severity::Information, "Start of program");
}

static void runGame()
{
    auto params = new Params();
    Menu::MainMenu menu;
    menu.createsButtons(params->world);

    params->game.setup(params->camera);

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, params, 0, 1);
#else
    while (!WindowShouldClose())
        drawFrame(params);
    CloseWindow();

    // Manual delete on purpose, we don't want params to be freed on the web
    delete params;
#endif
}

int main()
{
    setupLogger();

    std::shared_ptr<bmjs::Engine> jsEngine = bmjs::Engine::create();

    jsEngine->loadApi();
    jsEngine->loadScript("hello");

    /// Setup the locales parameters
    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");
    /// Setup Audio for the program
    raylib::core::scoped::AudioDevice audioDevice;
    /// Setup the Window
    raylib::core::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");
    raylib::core::Window::setTargetFPS(60);

    try {
        runGame();
    } catch (std::exception &e) {
        Logger::logger.log(Logger::Severity::Error,
            [&](std::ostream &writer) { writer << "Game stopped with exception: " << e.what(); });
    }

    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
