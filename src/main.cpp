#include <filesystem>
#include <iostream>
#include "localization/Localization.hpp"
#include "localization/Ressources.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Audio.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Sound.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/model/Animation.hpp"
#include "raylib/model/Model.hpp"
#include "raylib/raylib.hpp"

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

static void setupLogger()
{
    // Setup the logger parameters
    Logger::logger.setLogLevel(Logger::Severity::Information);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);
    Logger::logger.setName("main");
    raylib::initLogger(LOG_INFO);
}

///
///
///
///
///
///
struct Position : public ecs::Component , public raylib::core::Vector3 {
    Position(float px, float py, float pz) : raylib::core::Vector3(px, py, pz) {}
    Position(raylib::core::Vector3 &other) : raylib::core::Vector3(other) {}
};

struct Size : public ecs::Component, public raylib::core::Vector3 {
    Size(float sx, float sy, float sz) : raylib::core::Vector3(sx, sy, sz) {}
    Size(raylib::core::Vector3 &other) : raylib::core::Vector3(other) {}
};

struct CubeColor : public ecs::Component, public raylib::core::Color {
    CubeColor(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca) : raylib::core::Color(cr, cg, cb, ca) {}
    CubeColor(raylib::core::Color &other) : raylib::core::Color(other) {}
};

struct Cube : public ecs::Component {
    raylib::shapes::Cube cube;

    Cube() :cube() {}
    Cube(raylib::core::Vector3 position, raylib::core::Vector3 size, Color color) :cube(position, size, color) {}
};

struct ChangeCube : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        for (auto [cube, pos, col, size] : ecs::join(data.getStorage<Cube>(), data.getStorage<Position>(), data.getStorage<CubeColor>(), data.getStorage<Size>())) {
            cube.cube.setPosition(pos);
            cube.cube.setColor(col);
            cube.cube.setSize(size);
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

void game_loop()
{
    raylib::core::Camera3D camera;
    camera.setMode(raylib::core::Camera3D::CameraMode::ORBITAL);
    ecs::World world;

    world.addResource<ecs::Timer>();
    world.addSystem<ChangeCube>();
    world.addSystem<DrawingCube>();

    auto c1 = world.addEntity()
        .with<Position>(1.f, 3.f, 7.f)
        .with<Size>(5.f, 5.f, 5.f)
        .with<CubeColor>(250, 0, 0, 255)
        .with<Cube>()
        .build();

    auto c2 = world.addEntity()
        .with<Position>(0.f, 0.f, 0.f)
        .with<Size>(2.f, 2.f, 2.f)
        .with<CubeColor>(0, 0, 255, 255)
        .with<Cube>()
        .build();

    while (1) {
        camera.update();
        raylib::core::scoped::Drawing drawing;
        raylib::core::Window::clear(raylib::core::Color::GREEN);
        {
            raylib::core::scoped::Mode3D mode3D(camera);
            world.runSystems();
        };
        raylib::core::Window::drawFPS(10, 10);
    }

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

    /// Setup Audio for the program
    raylib::core::scoped::AudioDevice audioDevice;

    // Basic placeholder window
    raylib::core::Window::open(WIDTH, HEIGHT, "Bomberman: Global Offensive");

#if defined(PLATFORM_WEB)
    // We cannot use the WindowShouldClose() loop on the web,
    // since there is no such thing as a window.
    emscripten_set_main_loop_arg(&drawFrame, &camera, 0, 1);
#else
    raylib::core::Window::setTargetFPS(60);
    Logger::logger.log(Logger::Severity::Information, "Before game loop");

    game_loop();
#endif

    CloseWindow();
    localization::Localization::saveLocales();
    Logger::logger.log(Logger::Severity::Information, "End of program");
    return 0;
}
