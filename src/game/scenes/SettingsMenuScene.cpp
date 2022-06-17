/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsMenuScene
*/

#include "game/scenes/SettingsMenuScene.hpp"
#include "game/Engine.hpp"
#include "game/scenes/GameScene.hpp"

#include "logger/Logger.hpp"
#include "util/util.hpp"

#include "raylib/core/Audio.hpp"
#include "raylib/core/Vector2.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/core/scoped.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/KeyboardInput.hpp"
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

#include "game/resources/Engine.hpp"

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
        .with<game::components::Rectangle>()
        .with<game::components::Position>(34.f, 10.f)
        .with<game::components::Size>(32.f, 32.f)
        .with<game::components::Color>(raylib::core::Color::RED)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(35.f, 11.f)
        .with<game::components::Size>(30.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(36.f, 12.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsGraphics, 40, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(38.f, 20.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsFullscreen, 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::VOLUME_MUTE,
            game::gui::Widget::NullTag, game::SettingsMenuScene::BACK, game::SettingsMenuScene::RES_1)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::toggleFullscreen();
                Logger::logger.log(Logger::Severity::Debug, "Toggled fullscreen");
                if (raylib::core::Window::isFullscreen())
                    world.getResource<game::resources::EngineResource>().engine->getSettings().setFullscreen(true);
                else
                    world.getResource<game::resources::EngineResource>().engine->getSettings().setFullscreen(false);
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(38.f, 25.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsResolution, 20, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(40.f, 30.f)
        .with<game::components::Textual>("1280x720", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_1, game::SettingsMenuScene::VOLUME_100,
            game::SettingsMenuScene::RES_2, game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setSize(1280, 720);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setResolution(
                    raylib::core::Vector2(1280.f, 720.f));
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1280, 720)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(47.5f, 30.f)
        .with<game::components::Textual>("1366x768", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_2, game::SettingsMenuScene::RES_1,
            game::SettingsMenuScene::RES_3, game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setSize(1366, 768);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setResolution(
                    raylib::core::Vector2(1366.f, 768.f));
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1366, 768)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(55.f, 30.f)
        .with<game::components::Textual>("1920x1080", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_3, game::SettingsMenuScene::RES_2,
            game::gui::Widget::NullTag, game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setSize(1920, 1080);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setResolution(
                    raylib::core::Vector2(1920.f, 1080.f));
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
        .with<game::components::Rectangle>()
        .with<game::components::Position>(1.f, 10.f)
        .with<game::components::Size>(32.f, 32.f)
        .with<game::components::Color>(raylib::core::Color::BLUE)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(2.f, 11.f)
        .with<game::components::Size>(30.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(3.f, 12.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsAudio, 40, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(5.f, 20.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsMute, 20, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_MUTE, game::gui::Widget::NullTag,
            game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::BACK, game::SettingsMenuScene::VOLUME_25)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Audio::setMasterVolume(0.f);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(0.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 0%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(5.f, 25.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsVolume, 20, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(7.f, 30.f)
        .with<game::components::Textual>("25%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_25, game::gui::Widget::NullTag,
            game::SettingsMenuScene::VOLUME_50, game::SettingsMenuScene::VOLUME_MUTE, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Audio::setMasterVolume(25.f);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(25.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 25%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(12.f, 30.f)
        .with<game::components::Textual>("50%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_50, game::SettingsMenuScene::VOLUME_25,
            game::SettingsMenuScene::VOLUME_75, game::SettingsMenuScene::VOLUME_MUTE, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Audio::setMasterVolume(50.f);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(50.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 50%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(17.f, 30.f)
        .with<game::components::Textual>("75%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_75, game::SettingsMenuScene::VOLUME_50,
            game::SettingsMenuScene::VOLUME_100, game::SettingsMenuScene::VOLUME_MUTE, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Audio::setMasterVolume(75.f);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(75.f);
                Logger::logger.log(Logger::Severity::Debug, "Volume set to 75%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(22.f, 30.f)
        .with<game::components::Textual>("100%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_100, game::SettingsMenuScene::VOLUME_75,
            game::SettingsMenuScene::RES_1, game::SettingsMenuScene::VOLUME_MUTE, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Audio::setMasterVolume(100.f);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(100.f);
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
        .with<game::components::Rectangle>()
        .with<game::components::Position>(67.f, 10.f)
        .with<game::components::Size>(32.f, 32.f)
        .with<game::components::Color>(raylib::core::Color::GREEN)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(68.f, 11.f)
        .with<game::components::Size>(30.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(69.f, 12.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsKeybinds, 40, raylib::core::Color::GREEN)
        .build();
}

static void loadSettingsMenuScene(ecs::World &world)
{
    world.addStorage<game::KeyboardInput>();
    world.addStorage<game::gui::Checkable>();

    world.addEntity()
        .with<game::components::Position>(80.f, 3.f)
        .with<game::components::Textual>(localization::resources::rsBack, 30, raylib::core::Color::PURPLE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::BACK, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, game::SettingsMenuScene::FULLSCREEN, true)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->setScene<game::GameScene>();
                Logger::logger.log(Logger::Severity::Debug, "Back to menu");
                world.getResource<game::resources::EngineResource>().engine->getSettings().save();
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::PURPLE;
            })
        .build();

    loadGraphicSettings(world);
    loadAudioSettings(world);
    loadKeybindSettings(world);

    world.addEntity()
        .with<game::components::Position>(40.f, 2.f)
        .with<game::components::Textual>(localization::resources::rsSettings, 40, raylib::core::Color::YELLOW)
        .build();
}

namespace game
{
    SettingsMenuScene::SettingsMenuScene()
    {
        _world.addSystem<game::systems::DrawRectangle>();
        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::DrawText>();
        _world.addSystem<game::systems::DrawSelectedWidget>();

        _globalNoDraw.add<game::systems::InputManager>();
        _global2D.add<game::systems::DrawRectangle>();
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::DrawSelectedWidget>();

        _world.addResource<game::Users>();

        loadSettingsMenuScene(_world);
    }
} // namespace game
