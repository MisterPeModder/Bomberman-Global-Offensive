#include <filesystem>
#include <iostream>
#include <memory>
#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"
#include "game/components/Animation.hpp"
#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"
#include "game/systems/Animation.hpp"
#include "game/systems/Model.hpp"
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/model/Animation.hpp"
#include "raylib/model/Model.hpp"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

constexpr int WIDTH(500);
constexpr int HEIGHT(500);

static raylib::model::Model &getTestingModel()
{
    static const std::filesystem::path testModelPath =
        std::filesystem::path("assets").append("models").append("player").append("raylibguy.iqm");
    static raylib::model::Model model(testModelPath);

    return model;
}

static raylib::model::Animation &getTestingAnimation()
{
    static const std::filesystem::path testAnimPath =
        std::filesystem::path("assets").append("animations").append("player").append("raylibguy_anim.iqm");
    static raylib::model::Animation anim(testAnimPath);

    return anim;
}

struct params_s {
    raylib::core::Camera3D *camera;
    ecs::World *world;
};

static void drawFrame(void *arg)
{
    params_s *params = reinterpret_cast<params_s *>(arg);

    params->camera->update();
    raylib::core::scoped::Drawing drawing;
    raylib::core::Window::clear();
    {
        raylib::core::scoped::Mode3D mode3D(*params->camera);
        params->world->runSystems();
    };

    // DrawText("<insert great game here>", WIDTH / 2 - 120, HEIGHT / 2 - 1, 20, LIGHTGRAY);
    raylib::core::Window::drawFPS(10, 10);
}

static void raylibLogger(int msgType, const char *text, va_list args)
{
    static Logger raylibLogger("log_raylib.txt", true);
    Logger::Severity severity;
    std::array<char, 1024> buffer;

    switch (msgType) {
        case LOG_TRACE: severity = Logger::Severity::Debug; break;
        case LOG_DEBUG: severity = Logger::Severity::Debug; break;
        case LOG_INFO: severity = Logger::Severity::Information; break;
        case LOG_WARNING: severity = Logger::Severity::Warning; break;
        case LOG_ERROR: severity = Logger::Severity::Error; break;
        case LOG_FATAL: severity = Logger::Severity::Error; break;
        default: return;
    }
    vsnprintf(buffer.data(), 1024, text, args);
    raylibLogger.log(severity, buffer.data());
}

static void setupLogger()
{
    // Setup the logger parameters
    Logger::logger.setOutputFile("log.txt");
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);
    SetTraceLogCallback(raylibLogger);
    SetTraceLogLevel(LOG_INFO);
}

int main()
{
    setupLogger();

    /// Setup the locales parameters
    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << localization::Ressources::rsHello << std::endl;

    // Basic placeholder window
    raylib::core::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");
    raylib::core::Camera3D camera;
    camera.setMode(raylib::core::Camera3D::CameraMode::ORBITAL);

    raylib::core::Vector3 pos(0, -5, 0);
    raylib::core::Vector3 size(1, 1, 1);
    raylib::core::Vector3 rotationAxis(1, 0, 0);
    float rotationAngle = -90;

    raylib::model::Model &testingModel = getTestingModel();
    raylib::model::Animation &testingAnimation = getTestingAnimation();

    ecs::World world;
    world.addSystem<game::systems::DrawRotatedModel>();
    world.addSystem<game::systems::RunAnimation>();
    world.addEntity()
        .with<game::components::Model>(testingModel)
        .with<game::components::Position>(pos)
        .with<game::components::Size>(size)
        .with<game::components::RotationAngle>(rotationAngle)
        .with<game::components::RotationAxis>(rotationAxis)
        .with<game::components::Color>(raylib::core::Color::RED)
        .with<game::components::Animation>(testingAnimation)
        .build();

    params_s params;
    params.camera = &camera;
    params.world = &world;

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, &params, 0, 1);
#else
    raylib::core::Window::setTargetFPS(60);

    while (!raylib::core::Window::windowShouldClose())
        drawFrame(&params);
#endif

    CloseWindow();
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
