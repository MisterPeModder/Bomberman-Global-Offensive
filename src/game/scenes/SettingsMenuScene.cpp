/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsMenuScene
*/

#include "SettingsMenuScene.hpp"

#include "util/util.hpp"
#include "logger/Logger.hpp"

#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/core/Audio.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Position2D.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/components/Size2D.hpp"
#include "game/components/Textual.hpp"
#include "game/gui/components/Checkable.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "game/systems/Rectangle.hpp"

static void resizeWindow()
{
    static bool isChecked;

    if (!isChecked)
        raylib::core::Window::setSize(720, 360);
    else
        raylib::core::Window::setSize(1080, 720);
    isChecked = !isChecked;
}

static void loadGraphicSettings(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(480.f, 100.f)
        .with<game::components::Textual>("Graphic", 40, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(500.f, 200.f)
        .with<game::components::Textual>("Fullscreen", 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            raylib::core::Window::toggleFullscreen();
            world.getStorage<game::components::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(500.f, 300.f)
        .with<game::components::Textual>("Resolution", 20, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(425.f, 350.f)
        .with<game::components::Textual>("720x360", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            raylib::core::Window::setSize(720, 360);
            world.getStorage<game::components::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(525.f, 350.f)
        .with<game::components::Textual>("1080x720", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            raylib::core::Window::setSize(1080, 720);
            world.getStorage<game::components::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(625.f, 350.f)
        .with<game::components::Textual>("1920x1080", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            raylib::core::Window::setSize(1920, 1080);
            world.getStorage<game::components::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .build();
}

static void loadAudioSettings(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(150.f, 100.f)
        .with<game::components::Textual>("Audio", 40, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(170.f, 200.f)
        .with<game::components::Textual>("Mute", 20, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Audio::setMasterVolume(0.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 0%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(170.f, 300.f)
        .with<game::components::Textual>("Volume", 20, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(100.f, 350.f)
        .with<game::components::Textual>("25%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Audio::setMasterVolume(25.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 25%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(150.f, 350.f)
        .with<game::components::Textual>("50%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Audio::setMasterVolume(50.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 50%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(200.f, 350.f)
        .with<game::components::Textual>("75%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Audio::setMasterVolume(75.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 75%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(250.f, 350.f)
        .with<game::components::Textual>("100%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(1, 0, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Audio::setMasterVolume(100.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 100%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();
}

static void loadKeybindSettings(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(800.f, 100.f)
        .with<game::components::Textual>("Keybinds", 40, raylib::core::Color::GREEN)
        .build();
}

static void loadSettingsMenuScene(ecs::World &world)
{
    world.addSystem<game::systems::InputManager>();
    world.addSystem<game::systems::DrawText>();

    loadGraphicSettings(world);
    loadAudioSettings(world);
    loadKeybindSettings(world);

    // static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");

    // world.addSystem<game::systems::DrawModel>();
    // world.addStorage<game::components::Scale>();

    // world.addEntity()
    //     .with<game::components::Model>(testModelPath)
    //     .with<game::components::Position>(0.f, 0.f, 0.f)
    //     .with<game::components::Size>(3.f, 2.f, 1.f)
    //     .with<game::components::RotationAngle>(0)
    //     .with<game::components::RotationAxis>(0, 0, 0)
    //     .with<game::components::Color>(raylib::core::Color::BLUE)
    //     .build();

    // world.addEntity()
    //     .with<game::components::Position>(500.f, 200.f)
    //     .with<game::components::Textual>("Fullscreen", 20, raylib::core::Color::RED)
    //     .with<game::components::Controlable>(game::User::UserId::User1)
    //     .with<game::gui::Widget>(
    //         0, game::gui::Widget::NullTag, 1, game::gui::Widget::NullTag, game::gui::Widget::NullTag, true)
    //     .with<game::gui::Clickable>(
    //         [](ecs::Entity _) {
    //             (void)_;
    //             raylib::core::Window::toggleFullscreen();
    //         },
    //         [&](ecs::Entity btn, game::gui::Clickable::State state) {
    //             world.getStorage<game::components::Textual>()[btn.getId()].color =
    //                 (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::BLUE
    //                                                                 : raylib::core::Color::RED;
    //         })
    //     .build();

    // world.addEntity()
    //     .with<game::components::Position>(500.f, 300.f)
    //     .with<game::components::Textual>("Fullscreen but it's a different button", 20, raylib::core::Color::RED)
    //     .with<game::components::Controlable>(game::User::UserId::User1)
    //     .with<game::gui::Widget>(
    //         0, game::gui::Widget::NullTag, 1, game::gui::Widget::NullTag, game::gui::Widget::NullTag, true)
    //     .with<game::gui::Clickable>(
    //         [](ecs::Entity _) {
    //             (void)_;
    //             raylib::core::Window::toggleFullscreen();
    //         },
    //         [&](ecs::Entity btn, game::gui::Clickable::State state) {
    //             world.getStorage<game::components::Textual>()[btn.getId()].color =
    //                 (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::BLUE
    //                                                                 : raylib::core::Color::RED;
    //         })
    //     .build();


    world.addEntity()
        .with<game::components::Position>(450.f, 0.f)
        .with<game::components::Textual>("SETTINGS", 40, raylib::core::Color::YELLOW)
        .build();
}

namespace game
{
    void SettingsMenuScene::drawFrame()
    {
        raylib::core::scoped::Drawing drawing;
        raylib::core::Window::clear();
        _world.runSystems(_global2D);
        raylib::core::Window::drawFPS(10, 10);
    }

    SettingsMenuScene::SettingsMenuScene() : _currentSettingsMenu(GRAPHICS)
    {
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::InputManager>();

        _world.addResource<game::Users>();

        loadSettingsMenuScene(_world);
    }
} // namespace game
