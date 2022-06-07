#include <filesystem>
#include <iostream>
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/model/Animation.hpp"
#include "raylib/model/Model.hpp"

#include "util/util.hpp"
#include "raylib/shapes/Cube.hpp"
#include "raylib/shapes/Cone.hpp"
#include "raylib/core/Vector3.hpp"
#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"

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
    Vector3 pos(0, -5, 0);
    Vector3 scale(1, 1, 1);
    Vector3 rotationAxis(1, 0, 0);

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

///
///
///
///
///
///

struct Position : public ecs::Component , public Vector3 {

    Position(float x, float y, float z) : Vector3({x, y, z}) {}
    Position(Vector3 &other) : Vector3(other) {}
};

struct Size : public ecs::Component {
    Vector3 vector;

    Size(float x, float y, float z) : vector({x, y, z}) {}
    Size(Vector3 &other) : vector(other) {}
};


struct CubeColor : public ecs::Component {
    Color color;

    CubeColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : color(r, g, b, a) {}
};


struct Cube : public ecs::Component {
    raylib::shapes::Cube cube;

    Cube() :cube() {}
    Cube(Vector3 position, Vector3 size, Color color) :cube(position, size, color) {}
};

struct OurModel : public ecs::Component {
    raylib::model::Model model;

    OurModel() :model(util::makePath("assets", "models", "player", "raylibguy.iqm")) {}
};

struct ChangeCube : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        for (auto [cube, pos, col, size] : ecs::join(data.getStorage<Cube>(), data.getStorage<Position>(), data.getStorage<CubeColor>(), data.getStorage<Size>())) {
            cube.cube.setPosition(pos);
            cube.cube.setColor(col.color);
            cube.cube.setSize(size.vector);
        }
    }
};

struct DrawingCube : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        for (auto [cube] : ecs::join(data.getStorage<Cube>())) {
            cube.cube.draw();
        }
    }
};


struct DrawingModel : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        for (auto [model, pos, col] : ecs::join(data.getStorage<OurModel>(), data.getStorage<Position>(), data.getStorage<CubeColor>())) {
            model.model.draw(pos, 1, col.color);
        }
    }
};

void game_loop()
{

    raylib::core::Camera3D camera;
    camera.setMode(raylib::core::Camera3D::CameraMode::ORBITAL);
    ecs::World world;

    Vector3 pos(0, -5, 0);
    Vector3 scale(1, 1, 1);
    Vector3 rotationAxis(1, 0, 0);

    raylib::model::Model &testingModel = getTestingModel();

    Logger::logger.log(Logger::Severity::Debug, "Start loop");

    world.addResource<ecs::Timer>();
    world.addSystem<DrawingCube>();
    world.addSystem<DrawingModel>();

    auto ourCube =  world.addEntity()
                    .with<Position>(0.f, 0.f, 0.f)
                    .with<Size>(5.f, 5.f, 5.f)
                    .with<CubeColor>(255, 120, 50, 80)
                    .with<Cube>()
                    .build();
    auto ourModel =  world.addEntity()
                    .with<Position>(0.f, 0.f, 0.f)
                    .with<CubeColor>(0, 0, 250, 255)
                    .with<OurModel>()
                    .build();
    Logger::logger.log(Logger::Severity::Debug, "initialized");

    raylib::shapes::Cone cone;
    cone.setRadius(1, 1);
    cone.setColor((raylib::core::Color::BLUE).asRaylib());

    while (1) {
        camera.update();
        raylib::core::scoped::Drawing drawing;
        raylib::core::Window::clear(raylib::core::Color::GREEN);
        {
            raylib::core::scoped::Mode3D mode3D(camera);
            world.runSystems();
            cone.draw();
            testingModel.draw(pos, rotationAxis, -90, scale, raylib::core::Color::RED);
        };
        raylib::core::Window::drawFPS(10, 10);
    }

    Logger::logger.log(Logger::Severity::Debug, "End loop");

}

///
///
///
///
///

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

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, &camera, 0, 1);
#else
    raylib::core::Window::setTargetFPS(999);
    Logger::logger.log(Logger::Severity::Information, "Before game loop");

    game_loop();
#endif

    CloseWindow();
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
