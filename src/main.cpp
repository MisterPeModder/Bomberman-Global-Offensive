/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** main
*/

#include "ecs/World.hpp"

#include "game/Game.hpp"
#include "game/gui/components/Widget.hpp"

#include "localization/Localization.hpp"
#include "localization/Resources.hpp"

#include "logger/Logger.hpp"
#include "menu/MainMenu.hpp"

#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/raylib.hpp"
#include "raylib/textures/Image.hpp"

#include "game/Engine.hpp"
#include "script/Engine.hpp"

#include "util/util.hpp"

#include <memory>

constexpr int WIDTH(1080);
constexpr int HEIGHT(720);

static void setupLogger()
{
    // Setup the logger parameters
    Logger::logger.setLogLevel(Logger::Severity::Debug);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);
    Logger::logger.setName("main");
    raylib::initLogger(LOG_INFO);
    Logger::logger.log(Logger::Severity::Information, "Start of program");
}

int main()
{
    setupLogger();

    /// Setup the locales parameters
    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");

    /// Setup Audio for the program
    raylib::core::scoped::AudioDevice audioDevice;

    /// Setup the Window
    raylib::core::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");
    raylib::core::Window::setTargetFPS(60);
#ifndef __EMSCRIPTEN__
    raylib::textures::Image icon(util::makePath("assets", "icon.png"));
    raylib::core::Window::setIcon(icon);
#endif

    /// Create the game engine instance
#ifdef __EMSCRIPTEN__
    auto gameEnginePtr = new game::Engine;
#else
    auto gameEngine = std::make_unique<game::Engine>();
    game::Engine *gameEnginePtr = gameEngine.get();
#endif

    /// Start the Javascript engine
    std::shared_ptr<bmjs::Engine> jsEngine = bmjs::Engine::create(gameEnginePtr);

    jsEngine->loadApi();
    jsEngine->loadScript("hello");

    try {
        gameEnginePtr->run();
    } catch (std::exception const &e) {
        Logger::logger.log(Logger::Severity::Error,
            [&](std::ostream &writer) { writer << "Game stopped with exception: " << e.what(); });
    }

    raylib::core::Window::close();

    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
