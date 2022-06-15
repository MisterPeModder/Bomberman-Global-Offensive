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

#include "localization/Localization.hpp"
#include "localization/Resources.hpp"

static void loadGraphicSettings(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(480.f, 100.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsGraphic, 40, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(500.f, 200.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsFullscreen, 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::VOLUME_MUTE,
            game::gui::Widget::NullTag, game::gui::Widget::NullTag, game::SettingsMenuScene::RES_2, true)
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
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsResolution, 20, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(425.f, 350.f)
        .with<game::components::Textual>("720x360", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_1, game::SettingsMenuScene::VOLUME_100,
            game::SettingsMenuScene::RES_2, game::SettingsMenuScene::FULLSCREEN)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Window::setSize(720, 360);
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (720, 360)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(525.f, 350.f)
        .with<game::components::Textual>("1080x720", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_2, game::SettingsMenuScene::RES_1,
            game::SettingsMenuScene::RES_3, game::SettingsMenuScene::FULLSCREEN)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Window::setSize(1080, 720);
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1080, 720)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(625.f, 350.f)
        .with<game::components::Textual>("1920x1080", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_3, game::SettingsMenuScene::RES_2,
            game::gui::Widget::NullTag, game::SettingsMenuScene::FULLSCREEN)
        .with<game::gui::Clickable>(
            [](ecs::Entity _) {
                (void)_;
                raylib::core::Window::setSize(1920, 1080);
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1920, 1080)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();
}

static void loadAudioSettings(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(150.f, 100.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsAudio, 40, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(170.f, 200.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsMute, 20, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_MUTE, game::gui::Widget::NullTag,
            game::SettingsMenuScene::FULLSCREEN, game::gui::Widget::NullTag, game::SettingsMenuScene::VOLUME_50)
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
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsVolume, 20, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(100.f, 350.f)
        .with<game::components::Textual>("25%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_25, game::gui::Widget::NullTag,
            game::SettingsMenuScene::VOLUME_50, game::SettingsMenuScene::VOLUME_MUTE)
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
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_50, game::SettingsMenuScene::VOLUME_25,
            game::SettingsMenuScene::VOLUME_75, game::SettingsMenuScene::VOLUME_MUTE)
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
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_75, game::SettingsMenuScene::VOLUME_50,
            game::SettingsMenuScene::VOLUME_100, game::SettingsMenuScene::VOLUME_MUTE)
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
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_100, game::SettingsMenuScene::VOLUME_75,
            game::SettingsMenuScene::RES_1, game::SettingsMenuScene::VOLUME_MUTE)
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
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsKeybinds, 40, raylib::core::Color::GREEN)
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
        .with<game::components::Textual>(localization::resources::rsSettings, 40, raylib::core::Color::YELLOW)
        .build();
}

namespace game
{
    SettingsMenuScene::SettingsMenuScene()
    {
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::InputManager>();
        _global2D.add<game::systems::DrawSelectedWidget>();

        _world.addResource<game::Users>();

        loadSettingsMenuScene(_world);
    }
} // namespace game
