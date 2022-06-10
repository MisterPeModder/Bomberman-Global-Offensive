/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** main
*/

#include <filesystem>
#include <iostream>
#include "ecs/World.hpp"
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"

#include "game/gui/components/Widget.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/raylib.hpp"

#include "game/Game.hpp"

// #if defined(PLATFORM_WEB)
//     #include <emscripten/emscripten.h>
// #endif

constexpr int WIDTH(500);
constexpr int HEIGHT(500);

// static void drawFrame(void *arg)
// {
//     raylib::core::Camera3D *camera = reinterpret_cast<raylib::core::Camera3D *>(arg);
//     raylib::core::Vector3 pos(0, -5, 0);
//     raylib::core::Vector3 scale(1, 1, 1);
//     raylib::core::Vector3 rotationAxis(1, 0, 0);

//     raylib::model::Model &testingModel = getTestingModel();
//     raylib::model::Animation &testingAnimation = getTestingAnimation();

//     testingAnimation.updateModel(testingModel);
//     camera->update();
//     raylib::core::scoped::Drawing drawing;
//     raylib::core::Window::clear();
//     {
//         raylib::core::scoped::Mode3D mode3D(*camera);
//         // testingModel.draw(pos, rotationAxis, -90, scale, raylib::core::Color::RED);
//     };

//     world.runSystems();

//     // DrawText("<insert great game here>", WIDTH / 2 - 120, HEIGHT / 2 - 1, 20, LIGHTGRAY);
//     raylib::core::Window::drawFPS(10, 10);
// }

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
    ecs::World world;
    raylib::core::Camera3D camera;
    game::Game game(world, game::Game::Parameters(1));

    // world.addResource<game::Users>();
    // world.addSystem<game::DrawText>();
    // world.addSystem<game::InputManager>();

    // #if defined(PLATFORM_WEB)
    //     // We cannot use the WindowShouldClose() loop on the web,
    //     // since there is no such thing as a window.
    //     emscripten_set_main_loop_arg(&drawFrame, &camera, 0, 1);
    // #else
    // #endif

    world.addStorage<game::gui::Widget>();

    game.setup(camera);
    while (!WindowShouldClose()) {
        camera.update();
        game.drawFrame(camera);
    }

    CloseWindow();
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
