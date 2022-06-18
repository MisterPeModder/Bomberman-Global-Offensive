/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsMenuScene
*/

#include <algorithm>

#include "game/scenes/SettingsMenuScene.hpp"
#include "game/Engine.hpp"
#include "game/scenes/MainMenuScene.hpp"

#include "logger/Logger.hpp"
#include "util/util.hpp"

#include "raylib/core/Audio.hpp"
#include "raylib/core/Vector2.hpp"
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

#include "game/resources/Engine.hpp"

#include "game/systems/DrawSelectedWidget.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "game/systems/Rectangle.hpp"

#include "game/GameAction.hpp"

#include "localization/Localization.hpp"
#include "localization/Resources.hpp"

static void loadGraphicSettings(ecs::World &world, raylib::core::Vector2f pos, raylib::core::Vector2f size)
{
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x, pos.y)
        .with<game::components::Size>(size.x, size.y)
        .with<game::components::Color>(raylib::core::Color::RED)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x + 1, pos.y + 1)
        .with<game::components::Size>(size.x - 2, size.y - 2)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 2)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsGraphics, 40, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 4, pos.y + 10)
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
        .with<game::components::Position>(pos.x + 4, pos.y + 15)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsResolution, 20, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 6, pos.y + 20)
        .with<game::components::Textual>("1280x720", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_1, game::SettingsMenuScene::MUSIC_VOLUME_100,
            game::SettingsMenuScene::RES_2, game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::FPS_60)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->setResolution(
                    raylib::core::Vector2i(1280, 720));
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1280, 720)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 13.5f, pos.y + 20.f)
        .with<game::components::Textual>("1366x768", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_2, game::SettingsMenuScene::RES_1,
            game::SettingsMenuScene::RES_3, game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::FPS_144)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->setResolution(
                    raylib::core::Vector2i(1366, 768));
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1366, 768)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 21.f, pos.y + 20.f)
        .with<game::components::Textual>("1920x1080", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RES_3, game::SettingsMenuScene::RES_2,
            game::gui::Widget::NullTag, game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::FPS_240)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->setResolution(
                    raylib::core::Vector2i(1920, 1080));
                Logger::logger.log(Logger::Severity::Debug, "Window size set to (1920, 1080)");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 4.f, pos.y + 25.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsFPS, 20, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 6.f, pos.y + 30.f)
        .with<game::components::Textual>("30", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FPS_30, game::SettingsMenuScene::SFX_VOLUME_100,
            game::SettingsMenuScene::FPS_60, game::SettingsMenuScene::RES_1, game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setTargetFPS(30);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setTargetFramerate(30);
                Logger::logger.log(Logger::Severity::Debug, "FPS size set to 30");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 11.f, pos.y + 30.f)
        .with<game::components::Textual>("60", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FPS_60, game::SettingsMenuScene::FPS_30,
            game::SettingsMenuScene::FPS_144, game::SettingsMenuScene::RES_1, game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setTargetFPS(60);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setTargetFramerate(60);
                Logger::logger.log(Logger::Severity::Debug, "FPS size set to 60");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 16.f, pos.y + 30.f)
        .with<game::components::Textual>("144", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FPS_144, game::SettingsMenuScene::FPS_60,
            game::SettingsMenuScene::FPS_240, game::SettingsMenuScene::RES_2, game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setTargetFPS(144);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setTargetFramerate(144);
                Logger::logger.log(Logger::Severity::Debug, "FPS size set to 144");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 21.f, pos.y + 30.f)
        .with<game::components::Textual>("240", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FPS_240, game::SettingsMenuScene::FPS_144,
            game::gui::Widget::NullTag, game::SettingsMenuScene::RES_3, game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                raylib::core::Window::setTargetFPS(240);
                world.getResource<game::resources::EngineResource>().engine->getSettings().setTargetFramerate(240);
                Logger::logger.log(Logger::Severity::Debug, "FPS size set to 240");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();
}

static void loadAudioSettings(ecs::World &world, raylib::core::Vector2f pos, raylib::core::Vector2f size)
{
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x, pos.y)
        .with<game::components::Size>(size.x, size.y)
        .with<game::components::Color>(raylib::core::Color::BLUE)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x + 1, pos.y + 1)
        .with<game::components::Size>(size.x - 2, size.y - 2)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 2)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsAudio, 40, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 4.f, pos.y + 10.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsMuteUnmute, 20, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::VOLUME_MUTE, game::gui::Widget::NullTag,
            game::SettingsMenuScene::FULLSCREEN, game::SettingsMenuScene::BACK, game::SettingsMenuScene::MUSIC_VOLUME_0)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                if (world.getResource<game::resources::EngineResource>().engine->getSettings().getMasterVolume()
                    > 0.f) {
                    raylib::core::Audio::setMasterVolume(0.f);
                    world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(0.f);
                    Logger::logger.log(Logger::Severity::Debug, "Volume set to 0%");
                } else {
                    raylib::core::Audio::setMasterVolume(100.f);
                    world.getResource<game::resources::EngineResource>().engine->getSettings().setMasterVolume(100.f);
                    Logger::logger.log(Logger::Severity::Debug, "Volume set to 100%");
                }
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

#pragma region Music volume
    world.addEntity()
        .with<game::components::Position>(pos.x + 4.f, pos.y + 15.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsMusic, 20, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 6.f, pos.y + 20.f)
        .with<game::components::Textual>("0%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::MUSIC_VOLUME_0, game::gui::Widget::NullTag,
            game::SettingsMenuScene::MUSIC_VOLUME_33, game::SettingsMenuScene::VOLUME_MUTE,
            game::SettingsMenuScene::SFX_VOLUME_0)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMusicVolume(0.f);
                Logger::logger.log(Logger::Severity::Debug, "Music volume set to 0%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 11.f, pos.y + 20.f)
        .with<game::components::Textual>("33%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::MUSIC_VOLUME_33, game::SettingsMenuScene::MUSIC_VOLUME_0,
            game::SettingsMenuScene::MUSIC_VOLUME_66, game::SettingsMenuScene::VOLUME_MUTE,
            game::SettingsMenuScene::SFX_VOLUME_33)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMusicVolume(33.f);
                Logger::logger.log(Logger::Severity::Debug, "Music volume set to 33%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 16.f, pos.y + 20.f)
        .with<game::components::Textual>("66%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::MUSIC_VOLUME_66, game::SettingsMenuScene::MUSIC_VOLUME_33,
            game::SettingsMenuScene::MUSIC_VOLUME_100, game::SettingsMenuScene::VOLUME_MUTE,
            game::SettingsMenuScene::SFX_VOLUME_66)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMusicVolume(66.f);
                Logger::logger.log(Logger::Severity::Debug, "Music volume set to 66%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 21.f, pos.y + 20.f)
        .with<game::components::Textual>("100%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::MUSIC_VOLUME_100, game::SettingsMenuScene::MUSIC_VOLUME_66,
            game::SettingsMenuScene::RES_1, game::SettingsMenuScene::VOLUME_MUTE,
            game::SettingsMenuScene::SFX_VOLUME_100)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setMusicVolume(100.f);
                Logger::logger.log(Logger::Severity::Debug, "Music volume set to 100%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();
#pragma endregion

#pragma region Sfx volume
    world.addEntity()
        .with<game::components::Position>(pos.x + 4.f, pos.y + 25.f)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsSfx, 20, raylib::core::Color::BLUE)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 6.f, pos.y + 30.f)
        .with<game::components::Textual>("0%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::SFX_VOLUME_0, game::gui::Widget::NullTag,
            game::SettingsMenuScene::SFX_VOLUME_33, game::SettingsMenuScene::MUSIC_VOLUME_0,
            game::SettingsMenuScene::LANGUAGE_ENGLISH)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setSfxVolume(0.f);
                Logger::logger.log(Logger::Severity::Debug, "SFX volume set to 0%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 11.f, pos.y + 30.f)
        .with<game::components::Textual>("33%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::SFX_VOLUME_33, game::SettingsMenuScene::SFX_VOLUME_0,
            game::SettingsMenuScene::SFX_VOLUME_66, game::SettingsMenuScene::MUSIC_VOLUME_33,
            game::SettingsMenuScene::LANGUAGE_ENGLISH)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setSfxVolume(33.f);
                Logger::logger.log(Logger::Severity::Debug, "SFX volume set to 33%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 16.f, pos.y + 30.f)
        .with<game::components::Textual>("66%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::SFX_VOLUME_66, game::SettingsMenuScene::SFX_VOLUME_33,
            game::SettingsMenuScene::SFX_VOLUME_100, game::SettingsMenuScene::MUSIC_VOLUME_66,
            game::SettingsMenuScene::LANGUAGE_ENGLISH)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setSfxVolume(66.f);
                Logger::logger.log(Logger::Severity::Debug, "SFX volume set to 66%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 21.f, pos.y + 30.f)
        .with<game::components::Textual>("100%", 15, raylib::core::Color::BLUE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::SFX_VOLUME_100, game::SettingsMenuScene::SFX_VOLUME_66,
            game::SettingsMenuScene::FPS_30, game::SettingsMenuScene::MUSIC_VOLUME_100,
            game::SettingsMenuScene::LANGUAGE_ENGLISH)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->getSettings().setSfxVolume(100.f);
                Logger::logger.log(Logger::Severity::Debug, "SFX volume set to 100%");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();
#pragma endregion
}

static void loadControllerKeybindSettings(ecs::World &world, raylib::core::Vector2f pos, raylib::core::Vector2f size)
{
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x, pos.y)
        .with<game::components::Size>(size.x, size.y)
        .with<game::components::Color>(raylib::core::Color::GREEN)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x + 1, pos.y + 1)
        .with<game::components::Size>(size.x - 2, size.y - 2)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 2)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsKeybinds, 40, raylib::core::Color::GREEN)
        .build();
    world.addEntity()
        .with<game::components::Position>(pos.x + 4, pos.y + 8)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsControllerKeybinds, 20, raylib::core::Color::GREEN)
        .build();
}

static void loadKeyboardKeybindSettings(ecs::World &world, raylib::core::Vector2f pos, raylib::core::Vector2f size)
{
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x, pos.y)
        .with<game::components::Size>(size.x, size.y)
        .with<game::components::Color>(raylib::core::Color::GOLD)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x + 1, pos.y + 1)
        .with<game::components::Size>(size.x - 2, size.y - 2)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 2)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsKeybinds, 40, raylib::core::Color::GOLD)
        .build();
    world.addEntity()
        .with<game::components::Position>(pos.x + 4, pos.y + 8)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsKeyboardKeybinds, 20, raylib::core::Color::GOLD)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 12)
        .with<game::components::Textual>(
            localization::resources::keybinds::rsKeyBindLeft, 20, raylib::core::Color::GOLD)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT, game::SettingsMenuScene::LANGUAGE_ENGLISH,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT, game::SettingsMenuScene::FPS_60,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                Logger::logger.log(Logger::Severity::Error, "Button must be set");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::GOLD;
            })
        .build();
    world.addEntity()
        .with<game::components::Position>(pos.x + 8, pos.y + 12)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::components::Textual>(

                    "value"

                    // std::find_if(world.getResource<game::resources::EngineResource>().engine->getUsers()[game::User::UserId::User1].getProfile().getKeybinds().getKeyboardBindings().begin(), world.getResource<game::resources::EngineResource>().engine->getUsers()[game::User::UserId::User1].getProfile().getKeybinds().getKeyboardBindings().end(), game::GameAction::MOVE_LEFT) != world.getResource<game::resources::EngineResource>().engine->getUsers()[game::User::UserId::User1].getProfile().getKeybinds().getKeyboardBindings().begin() ? "ok" : "not ok"

                    // world.getResource<game::resources::EngineResource>().engine->getUsers()[game::User::UserId::User1].getProfile().getKeybinds().getKeyboardBindings().

                , 20, raylib::core::Color::GOLD)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 16, pos.y + 12)
        .with<game::components::Textual>(
            localization::resources::keybinds::rsKeyBindRight, 20, raylib::core::Color::GOLD)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT, game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT,
            game::gui::Widget::NullTag, game::SettingsMenuScene::FPS_240,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_DOWN)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                Logger::logger.log(Logger::Severity::Error, "Button must be set");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::GOLD;
            })
        .build();
    world.addEntity()
        .with<game::components::Position>(pos.x + 22, pos.y + 12)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::components::Textual>(

                    "value"

                , 20, raylib::core::Color::GOLD)
        .build();



        

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 17)
        .with<game::components::Textual>(
            localization::resources::keybinds::rsKeyBindUp, 20, raylib::core::Color::GOLD)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP, game::SettingsMenuScene::LANGUAGE_FRENCH,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_DOWN, game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_BOMB)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                Logger::logger.log(Logger::Severity::Error, "Button must be set");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::GOLD;
            })
        .build();
    world.addEntity()
        .with<game::components::Position>(pos.x + 8, pos.y + 17)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::components::Textual>(

                    "value"

                , 20, raylib::core::Color::GOLD)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 16, pos.y + 17)
        .with<game::components::Textual>(
            localization::resources::keybinds::rsKeyBindDown, 20, raylib::core::Color::GOLD)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::KEYBINDS_KEYBOARD_DOWN, game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP,
            game::gui::Widget::NullTag, game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                Logger::logger.log(Logger::Severity::Error, "Button must be set");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::GOLD;
            })
        .build();
    world.addEntity()
        .with<game::components::Position>(pos.x + 22, pos.y + 17)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::components::Textual>(

                    "value"

                , 20, raylib::core::Color::GOLD)
        .build();
}

static void loadLanguageSettings(ecs::World &world, raylib::core::Vector2f pos, raylib::core::Vector2f size)
{
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x, pos.y)
        .with<game::components::Size>(size.x, size.y)
        .with<game::components::Color>(raylib::core::Color::PURPLE)
        .build();
    world.addEntity()
        .with<game::components::Rectangle>()
        .with<game::components::Position>(pos.x + 1, pos.y + 1)
        .with<game::components::Size>(size.x - 2, size.y - 2)
        .with<game::components::Color>(raylib::core::Color::BLACK)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 2, pos.y + 2)
        .with<game::components::Textual>(
            localization::resources::settings::rsSettingsLanguage, 40, raylib::core::Color::PURPLE)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 4, pos.y + 10)
        .with<game::components::Textual>(
            localization::resources::languages::rsLanguageEnglish, 20, raylib::core::Color::PURPLE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::LANGUAGE_ENGLISH, game::gui::Widget::NullTag,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT, game::SettingsMenuScene::SFX_VOLUME_0,
            game::SettingsMenuScene::LANGUAGE_FRENCH)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                localization::Localization::setLocale("en");
                world.getResource<game::resources::EngineResource>().engine->getSettings().setLocale("en");
                Logger::logger.log(Logger::Severity::Debug, "Set language to English");
                world.getResource<game::resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::PURPLE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 4, pos.y + 15)
        .with<game::components::Textual>(
            localization::resources::languages::rsLanguageFrench, 20, raylib::core::Color::PURPLE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::LANGUAGE_FRENCH, game::gui::Widget::NullTag,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP, game::SettingsMenuScene::LANGUAGE_ENGLISH, game::SettingsMenuScene::BACK)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                localization::Localization::setLocale("fr");
                world.getResource<game::resources::EngineResource>().engine->getSettings().setLocale("fr");
                Logger::logger.log(Logger::Severity::Debug, "Set language to French");
                world.getResource<game::resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::PURPLE;
            })
        .build();
}

static void loadSettingsMenuScene(ecs::World &world)
{
    world.addEntity()
        .with<game::components::Position>(67.f, 3.f)
        .with<game::components::Textual>(localization::resources::rsBack, 30, raylib::core::Color::YELLOW)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::BACK, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, game::SettingsMenuScene::FULLSCREEN, true)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                world.getResource<game::resources::EngineResource>().engine->setScene<game::MainMenuScene>();
                Logger::logger.log(Logger::Severity::Debug, "Back to menu");
                world.getResource<game::resources::EngineResource>().engine->getSettings().save();
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::YELLOW;
            })
        .build();

    loadGraphicSettings(world, raylib::core::Vector2f(34, 10), raylib::core::Vector2f(32, 40));
    loadAudioSettings(world, raylib::core::Vector2f(1, 10), raylib::core::Vector2f(32, 40));
    loadControllerKeybindSettings(world, raylib::core::Vector2f(67, 10), raylib::core::Vector2f(32, 88));
    loadKeyboardKeybindSettings(world, raylib::core::Vector2f(34, 52), raylib::core::Vector2f(32, 46));
    loadLanguageSettings(world, raylib::core::Vector2f(1, 52), raylib::core::Vector2f(32, 46));

    world.addEntity()
        .with<game::components::Position>(34.f, 2.f)
        .with<game::components::Textual>(localization::resources::rsSettings, 40, raylib::core::Color::WHITE)
        .build();

    world.addEntity()
        .with<game::components::Position>(1.f, 2.f)
        .with<game::components::Textual>(localization::resources::rsShortTitle, 40, raylib::core::Color::YELLOW)
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

        loadSettingsMenuScene(_world);
    }
} // namespace game
