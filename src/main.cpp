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
#include "raylib/core/Audio.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/core/Sound.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/model/Animation.hpp"
#include "raylib/model/Model.hpp"
#include "raylib/raylib.hpp"

#include "ecs/Storage.hpp"
#include "game/Users.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Position.hpp"
#include "game/components/Textual.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"

#include "game/gui/components/Checkable.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

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

static void setupLogger()
{
    // Setup the logger parameters
    Logger::logger.setLogLevel(Logger::Severity::Debug);
    Logger::logger.setLogInfo(Logger::LogInfo::Time);
    Logger::logger.setName("main");
    raylib::initLogger(LOG_INFO);
}

static void addTestWidgets(ecs::World &world)
{
    world.addEntity()
        .with<game::Position>(0.f, 0.f)
        .with<game::Textual>("I'm the ECS button", 20, raylib::core::Color::RED)
        .with<game::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(
            0, game::gui::Widget::NullTag, 1, game::gui::Widget::NullTag, game::gui::Widget::NullTag, true)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                Logger::logger.log(Logger::Severity::Debug, "On click event!");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::Textual>()[btn.getId()].color = (state == game::gui::Clickable::State::Pressed)
                    ? raylib::core::Color::BLUE
                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::Position>(0.f, 100.f)
        .with<game::Textual>("Hello ECS", 40, raylib::core::Color::RED)
        .with<game::Controlable>(game::User::UserId::User1,
            [](ecs::Entity self, ecs::SystemData data, const game::Users::ActionEvent &event) {
                (void)self;
                (void)data;
                (void)event;
                Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                    writer << "Text control! " << event.value << ", " << static_cast<size_t>(event.action);
                });
                return false;
            })
        .build();

    world.addEntity()
        .with<game::Position>(250.f, 0.f)
        .with<game::Textual>("I'm the ECS Checkbox!", 20, raylib::core::Color::RED)
        .with<game::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            world.getStorage<game::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .build();
}

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
        .with<game::Model>(testingModel)
        .with<game::Position>(pos)
        .with<game::Size>(size)
        .with<game::RotationAngle>(rotationAngle)
        .with<game::RotationAxis>(rotationAxis)
        .with<game::Color>(raylib::core::Color::RED)
        .with<game::Animation>(testingAnimation)
        .build();

    addTestWidgets(world);

    world.addResource<game::Users>();
    world.addSystem<game::DrawText>();
    world.addSystem<game::InputManager>();

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
