/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsMenuScene
*/

#include "SettingsMenuScene.hpp"

#include "logger/Logger.hpp"
#include "util/util.hpp"

#include "raylib/core/Audio.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"

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

#include "game/systems/DrawSelectedWidget.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "game/systems/Rectangle.hpp"

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
        .with<game::gui::Widget>(
            0, game::gui::Widget::NullTag, 1, game::gui::Widget::NullTag, game::gui::Widget::NullTag, true)
        .with<game::gui::Checkable>([&](ecs::Entity checkbox, bool checked) {
            raylib::core::Window::toggleFullscreen();
            Logger::logger.log(Logger::Severity::Debug, "Toggled fullscreen");
            world.getStorage<game::components::Textual>()[checkbox.getId()].color =
                (checked) ? raylib::core::Color::BLUE : raylib::core::Color::RED;
        })
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Window::toggleFullscreen();
                Logger::logger.log(Logger::Severity::Debug, "Toggled fullscreen");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
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
    world.addSystem<game::systems::DrawSelectedWidget>();

    loadGraphicSettings(world);
    loadAudioSettings(world);
    loadKeybindSettings(world);

    world.addEntity()
        .with<game::components::Position>(450.f, 0.f)
        .with<game::components::Textual>("SETTINGS", 40, raylib::core::Color::YELLOW)
        .build();
}

namespace game
{
    SettingsMenuScene::SettingsMenuScene() : _currentSettingsMenu(GRAPHICS)
    {
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::InputManager>();
        _global2D.add<game::systems::DrawSelectedWidget>();

        _world.addResource<game::Users>();

        loadSettingsMenuScene(_world);
    }
} // namespace game
