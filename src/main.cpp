#include <filesystem>
#include <iostream>
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/core/Audio.hpp"
#include "raylib/core/Sound.hpp"
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

static void drawFrame(void *arg)
{
    raylib::core::Camera3D *camera = reinterpret_cast<raylib::core::Camera3D *>(arg);
    raylib::core::Vector3 pos(0, -5, 0);
    raylib::core::Vector3 scale(1, 1, 1);
    raylib::core::Vector3 rotationAxis(1, 0, 0);

    raylib::model::Model &testingModel = getTestingModel();
    raylib::model::Animation &testingAnimation = getTestingAnimation();

    testingAnimation.updateModel(testingModel);
    camera->update();
    raylib::core::scoped::Drawing drawing;
    raylib::core::Window::clear();
    {
        raylib::core::scoped::Mode3D mode3D(*camera);
        testingModel.draw(pos, rotationAxis, -90, scale, raylib::core::Color::RED);
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

    ///setup audio for program
    raylib::core::Audio audio;
    audio.initAudioDevice();

    // Basic placeholder window
    raylib::core::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");
    raylib::core::Camera3D camera;
    camera.setMode(raylib::core::Camera3D::CameraMode::ORBITAL);

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, &camera, 0, 1);
#else
    raylib::core::Window::setTargetFPS(60);

    while (!WindowShouldClose())
        drawFrame(&camera);
#endif

    audio.closeAudioDevice();
    CloseWindow();
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
