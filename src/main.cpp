#include <iostream>
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"

#include "bomberman/map/Map.hpp"

#include <raylib.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

constexpr int WIDTH(500);
constexpr int HEIGHT(500);

static void drawFrame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("<insert great game here>", WIDTH / 2 - 120, HEIGHT / 2 - 1, 20, LIGHTGRAY);
    EndDrawing();
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
    Logger::logger.setLogLevel(Logger::Severity::Debug);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);
    SetTraceLogCallback(raylibLogger);
    SetTraceLogLevel(LOG_INFO);
}

int main()
{
    bomberman::map::Map map;

    setupLogger();

    Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) { writer << '\n' << map; });

    /// Setup the locales parameters
    localization::Localization::loadLocales({"en", "fr"});
    localization::Localization::setLocale("fr");

    Logger::logger.log(Logger::Severity::Information, "Start of program");
    std::cout << localization::Ressources::rsHello << std::endl;

    // Basic placeholder window
    InitWindow(WIDTH, HEIGHT, "Bomberman: Global Offensive");

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop(&drawFrame, 0, 1);
#else
    SetTargetFPS(60);

    while (!WindowShouldClose())
        drawFrame();
#endif

    CloseWindow();
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
