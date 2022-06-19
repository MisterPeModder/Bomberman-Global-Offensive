/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** SettingsMenuScene
*/

#include <algorithm>

#include "game/Engine.hpp"
#include "game/components/Identity.hpp"
#include "game/scenes/MainMenuScene.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include <sstream>
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
#include "localization/ResourceString.hpp"
#include "localization/Resources.hpp"

#include "game/components/KeybindIntercepter.hpp"
#include "game/systems/KeybindIntercept.hpp"

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
            game::SettingsMenuScene::KEYBINDS_GAMEPAD_FIRST, game::SettingsMenuScene::FULLSCREEN,
            game::SettingsMenuScene::FPS_240)
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
        .with<game::components::Textual>(localization::resources::settings::rsSettingsFPS, 20, raylib::core::Color::RED)
        .build();

    world.addEntity()
        .with<game::components::Position>(pos.x + 6.f, pos.y + 30.f)
        .with<game::components::Textual>("30", 15, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::FPS_30, game::SettingsMenuScene::SFX_VOLUME_100,
            game::SettingsMenuScene::FPS_60, game::SettingsMenuScene::RES_1,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT)
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
            game::SettingsMenuScene::FPS_144, game::SettingsMenuScene::RES_1,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT)
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
            game::SettingsMenuScene::FPS_240, game::SettingsMenuScene::RES_2,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT)
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
            game::SettingsMenuScene::getGamepadWidgetId(
                game::SettingsMenuScene::KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0),
            game::SettingsMenuScene::RES_3, game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT)
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
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP, game::SettingsMenuScene::LANGUAGE_ENGLISH,
            game::SettingsMenuScene::BACK)
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
        .with<game::gui::Widget>(game::SettingsMenuScene::BACK, game::gui::Widget::NullTag,
            game::SettingsMenuScene::RESET, game::gui::Widget::NullTag, game::SettingsMenuScene::KEYBINDS_GAMEPAD_FIRST,
            true)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            Logger::logger.log(Logger::Severity::Debug, "Back to menu");
            auto engine = world.getResource<game::resources::EngineResource>().engine;

            engine->getSettings().save();
            engine->getUsers().save();
            engine->setScene<game::MainMenuScene>();
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(77.f, 3.f)
        .with<game::components::Textual>(localization::resources::rsReset, 30, raylib::core::Color::YELLOW)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::SettingsMenuScene::RESET, game::SettingsMenuScene::BACK,
            game::gui::Widget::NullTag, game::gui::Widget::NullTag, game::SettingsMenuScene::KEYBINDS_GAMEPAD_FIRST)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            Logger::logger.log(Logger::Severity::Debug, "Reloaded default settings");
            auto engine = world.getResource<game::resources::EngineResource>().engine;
            engine->getSettings().loadDefaults();
            engine->getUsers().loadDefaults();
            engine->setScene<game::SettingsMenuScene>();
        })
        .build();

    loadGraphicSettings(world, raylib::core::Vector2f(34, 10), raylib::core::Vector2f(32, 40));
    loadAudioSettings(world, raylib::core::Vector2f(1, 10), raylib::core::Vector2f(32, 40));
    // loadControllerKeybindSettings(world, raylib::core::Vector2f(67, 10), raylib::core::Vector2f(32, 88));
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
    SettingsMenuScene::SettingsMenuScene() {}

    void SettingsMenuScene::setupWorld()
    {
        _world.addSystem<game::systems::DrawRectangle>();
        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::DrawText>();
        _world.addSystem<game::systems::DrawSelectedWidget>();
        _world.addSystem<game::systems::KeybindIntercept>();
        _world.addStorage<game::components::KeybindIntercepter>();

        _globalNoDraw.add<game::systems::InputManager, game::systems::KeybindIntercept>();
        _global2D.add<game::systems::DrawRectangle>();
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::DrawSelectedWidget>();

        loadSettingsMenuScene(_world);
        loadSection({raylib::core::Vector2f(34, 52), raylib::core::Vector2f(32, 46), raylib::core::Color::GOLD,
                        localization::resources::settings::rsSettingsKeybinds},
            [this](auto &sct) { _loadKeyboardKeybinds(sct); });

        loadSection({raylib::core::Vector2f(67, 10), raylib::core::Vector2f(32, 88), raylib::core::Color::GREEN,
                        localization::resources::settings::rsSettingsKeybinds},
            [this](auto &sct) { _loadGamepadKeybinds(sct); });
    }

    void SettingsMenuScene::loadSection(Section section, std::function<void(const Section &)> onLoad)
    {
        _world.addEntity()
            .with<game::components::Rectangle>()
            .with<game::components::Position>(section.pos.x, section.pos.y)
            .with<game::components::Size>(section.size.x, section.size.y)
            .with<game::components::Color>(section.color)
            .build();
        _world.addEntity()
            .with<game::components::Rectangle>()
            .with<game::components::Position>(section.pos.x + 1, section.pos.y + 1)
            .with<game::components::Size>(section.size.x - 2, section.size.y - 2)
            .with<game::components::Color>(raylib::core::Color::BLACK)
            .build();

        _world.addEntity()
            .with<game::components::Position>(section.pos.x + 2, section.pos.y + 2)
            .with<game::components::Textual>(section.name, 40, section.color)
            .build();

        onLoad(section);
    }

    void SettingsMenuScene::_updateActionKey(GameAction action)
    {
        std::stringstream ss;
        auto &binds = _world.getResource<game::resources::EngineResource>()
                          .engine->getUsers()[game::User::UserId::User1]
                          .getKeybinds()
                          .getKeyboardBindings();

        for (auto iter : binds)
            if (iter.action == action) {
                ss << static_cast<char>(iter.key);
                break;
            }

        for (auto [text, id] : ecs::join(
                 _world.getStorage<game::components::Textual>(), _world.getStorage<game::components::Identity>())) {
            if (id.id == _actionsKeyboardBindings[static_cast<size_t>(action)]) {
                text.text = ss.str();
                return;
            }
        }
    }

    void SettingsMenuScene::_loadKeyboardKeybinds(const Section &sct)
    {
        _world.addEntity()
            .with<game::components::Position>(sct.pos.x + 4, sct.pos.y + 8)
            .with<game::components::Textual>(
                localization::resources::settings::rsSettingsKeyboardKeybinds, 20, sct.color)
            .build();

        auto addAction = [&, this](raylib::core::Vector2f posName, raylib::core::Vector2f posValue, GameAction action,
                             std::string_view actionName, gui::Widget::WidgetId id,
                             gui::Widget::WidgetId left = gui::Widget::NullTag,
                             gui::Widget::WidgetId right = gui::Widget::NullTag,
                             gui::Widget::WidgetId up = gui::Widget::NullTag,
                             gui::Widget::WidgetId down = gui::Widget::NullTag) {
            auto btn = _world.addEntity()
                           .with<game::components::Position>(sct.pos.x + posValue.x, sct.pos.y + posValue.y)
                           .with<game::components::Controlable>(game::User::UserId::User1)
                           .with<game::components::Identity>()
                           .with<game::components::Textual>("", 20, sct.color)
                           .build();
            _actionsKeyboardBindings[static_cast<size_t>(action)] =
                _world.getStorage<game::components::Identity>()[btn.getId()].id;

            _world.addEntity()
                .with<game::components::Position>(sct.pos.x + posName.x, sct.pos.y + posName.y)
                .with<game::components::Textual>(actionName, 20, sct.color)
                .with<game::components::Controlable>(game::User::UserId::User1)
                .with<game::gui::Widget>(id, left, right, up, down)
                .with<game::gui::Clickable>(
                    [=, this](ecs::Entity) {
                        if (!_world.getResource<game::resources::EngineResource>()
                                 .engine->getUsers()[game::User::UserId::User1]
                                 .isKeyboard())
                            return;
                        _world.addEntity()
                            .with<game::components::KeybindIntercepter>(
                                game::User::UserId::User1, action, [=, this]() { _updateActionKey(action); })
                            .build();
                        Logger::logger.log(Logger::Severity::Information, "Waiting for user keyboard input");
                    },
                    [=, this](ecs::Entity clickable, game::gui::Clickable::State state) {
                        _world.getStorage<game::components::Textual>()[clickable.getId()].color =
                            (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW : sct.color;
                    })
                .build();
            _updateActionKey(action);
        };

        addAction({4, 13}, {10, 13}, GameAction::MOVE_LEFT, localization::resources::keybinds::rsKeyBindLeft,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT, game::SettingsMenuScene::LANGUAGE_ENGLISH,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT, game::SettingsMenuScene::FPS_60,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP);
        addAction({18, 13}, {24, 13}, GameAction::MOVE_RIGHT, localization::resources::keybinds::rsKeyBindRight,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT, game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0), game::SettingsMenuScene::FPS_240,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_DOWN);
        addAction({4, 18}, {10, 18}, GameAction::MOVE_UP, localization::resources::keybinds::rsKeyBindUp,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP, game::SettingsMenuScene::LANGUAGE_FRENCH,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_DOWN, game::SettingsMenuScene::KEYBINDS_KEYBOARD_LEFT,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_BOMB);
        addAction({18, 18}, {24, 18}, GameAction::MOVE_DOWN, localization::resources::keybinds::rsKeyBindDown,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_DOWN, game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0),
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_RIGHT, game::SettingsMenuScene::KEYBINDS_KEYBOARD_BOMB);

        addAction({4, 25}, {24, 25}, GameAction::PLACE_BOMB, localization::resources::keybinds::rsKeyBindBomb,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_BOMB, game::SettingsMenuScene::LANGUAGE_FRENCH,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0), game::SettingsMenuScene::KEYBINDS_KEYBOARD_UP,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE);
        addAction({4, 30}, {24, 30}, GameAction::ACTIVATE_ITEM, localization::resources::keybinds::rsKeyBindActivable,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE, game::SettingsMenuScene::LANGUAGE_FRENCH,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0), game::SettingsMenuScene::KEYBINDS_KEYBOARD_BOMB,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE_PREVIOUS);

        addAction({4, 35}, {24, 35}, GameAction::PREVIOUS_ACTIVABLE,
            localization::resources::keybinds::rsKeyBindActivablePrevious,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE_PREVIOUS, game::SettingsMenuScene::LANGUAGE_FRENCH,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0),
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE_NEXT);
        addAction({4, 40}, {24, 40}, GameAction::NEXT_ACTIVABLE,
            localization::resources::keybinds::rsKeyBindActivableNext,
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE_NEXT, game::SettingsMenuScene::LANGUAGE_FRENCH,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, 0),
            game::SettingsMenuScene::KEYBINDS_KEYBOARD_ACTIVABLE_PREVIOUS, game::SettingsMenuScene::BACK);
    }

    void SettingsMenuScene::_updateActionGamepad(GameAction action, size_t userId)
    {
        std::string_view buttonString;

        auto &binds = _world.getResource<game::resources::EngineResource>()
                          .engine->getUsers()[static_cast<game::User::UserId>(userId)]
                          .getKeybinds()
                          .getGamepadBindings();

        for (auto iter : binds)
            if (iter.action == action && iter.input.isButton()) {
                buttonString = _gamepadButtonStrings[iter.input.getButton()];
                break;
            }

        for (auto [text, id] : ecs::join(
                 _world.getStorage<game::components::Textual>(), _world.getStorage<game::components::Identity>())) {
            if (id.id == _actionsGamepadBindings[userId][static_cast<size_t>(action)]) {
                text.text = buttonString;
                return;
            }
        }
    }

    int SettingsMenuScene::getGamepadWidgetId(WIDGET_GAMEPAD_ID action, size_t user)
    {
        return static_cast<int>(action)
            + (static_cast<int>(KEYBINDS_GAMEPAD_FIRST) + static_cast<int>(KEYBINDS_GAMEPAD_COUNT) * user);
    }

    void SettingsMenuScene::_loadGamepadProfile(const Section &sct, size_t id)
    {
        std::string name;
        raylib::core::Vector2f offset(0.f, 20.f * id);
        User::UserId userId = static_cast<User::UserId>(id);

        switch (id) {
            case 0: name = localization::resources::rsUser1; break;
            case 1: name = localization::resources::rsUser2; break;
            case 2: name = localization::resources::rsUser3; break;
            default: name = localization::resources::rsUser4; break;
        }

        _world.addEntity()
            .with<game::components::Position>(sct.pos.x + 2, sct.pos.y + 13 + offset.y)
            .with<game::components::Textual>(name, 20, sct.color)
            .build();

        auto addAction = [&, this](raylib::core::Vector2f posName, raylib::core::Vector2f posValue, GameAction action,
                             std::string_view actionName, gui::Widget::WidgetId widgetId,
                             gui::Widget::WidgetId left = gui::Widget::NullTag,
                             gui::Widget::WidgetId right = gui::Widget::NullTag,
                             gui::Widget::WidgetId up = gui::Widget::NullTag,
                             gui::Widget::WidgetId down = gui::Widget::NullTag) {
            auto btn = _world.addEntity()
                           .with<game::components::Position>(sct.pos.x + posValue.x, sct.pos.y + posValue.y + offset.y)
                           .with<game::components::Controlable>(game::User::UserId::User1)
                           .with<game::components::Identity>()
                           .with<game::components::Textual>("value", 15, sct.color)
                           .build();
            _actionsGamepadBindings[id][static_cast<size_t>(action)] =
                _world.getStorage<game::components::Identity>()[btn.getId()].id;

            _world.addEntity()
                .with<game::components::Position>(sct.pos.x + posName.x, sct.pos.y + posName.y + offset.y)
                .with<game::components::Textual>(actionName, 15, sct.color)
                .with<game::components::Controlable>(userId)
                .with<game::gui::Widget>(widgetId, left, right, up, down, (action == GameAction::PLACE_BOMB && id > 0))
                .with<game::gui::Clickable>(
                    [=, this](ecs::Entity) {
                        if (_world.getResource<game::resources::EngineResource>()
                                .engine->getUsers()[userId]
                                .isKeyboard())
                            return;
                        _world.addEntity()
                            .with<game::components::KeybindIntercepter>(
                                userId, action, [=, this]() { _updateActionGamepad(action, id); }, false)
                            .build();
                        Logger::logger.log(Logger::Severity::Information, "Waiting for user gamepad input");
                    },
                    [=, this](ecs::Entity clickable, game::gui::Clickable::State state) {
                        _world.getStorage<game::components::Textual>()[clickable.getId()].color =
                            (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW : sct.color;
                    })
                .build();
            _updateActionGamepad(action, id);
        };

        addAction({4, 18}, {10, 18}, GameAction::PLACE_BOMB, localization::resources::keybinds::rsKeyBindBomb,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_BOMB, id), (id == 0) ? static_cast<int>(RES_3) : gui::Widget::NullTag,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_ACTIVABLE, id),
            (id == 0) ? static_cast<int>(BACK) : gui::Widget::NullTag,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, id));
        addAction({16, 18}, {22, 18}, GameAction::ACTIVATE_ITEM,
            localization::resources::keybinds::rsKeyBindActivableShort,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_ACTIVABLE, id), getGamepadWidgetId(KEYBINDS_GAMEPAD_BOMB, id),
            gui::Widget::NullTag, (id == 0) ? static_cast<int>(BACK) : gui::Widget::NullTag,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_NEXT_ACTIVABLE, id));

        addAction({4, 23}, {10, 23}, GameAction::PREVIOUS_ACTIVABLE,
            localization::resources::keybinds::rsKeyBindActivablePreviousShort,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, id),
            (id == 0) ? static_cast<int>(RES_3) : gui::Widget::NullTag,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_NEXT_ACTIVABLE, id), getGamepadWidgetId(KEYBINDS_GAMEPAD_BOMB, id));
        addAction({16, 23}, {22, 23}, GameAction::NEXT_ACTIVABLE,
            localization::resources::keybinds::rsKeyBindActivableNextShort,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_NEXT_ACTIVABLE, id),
            getGamepadWidgetId(KEYBINDS_GAMEPAD_PREVIOUS_ACTIVABLE, id), gui::Widget::NullTag,
            getGamepadWidgetId(KEYBINDS_GAMEPAD_ACTIVABLE, id));
    }

    void SettingsMenuScene::_fillGamepadButtonStrings()
    {
        using Btn = raylib::core::Gamepad::Button;

        _gamepadButtonStrings[Btn::UNKNOWN] = localization::resources::keybinds::controller::rsUnknown;
        /// D-Pad
        _gamepadButtonStrings[Btn::DPAD_FACE_UP] = localization::resources::keybinds::controller::rsDPadUP;
        _gamepadButtonStrings[Btn::DPAD_FACE_RIGHT] = localization::resources::keybinds::controller::rsDPadRight;
        _gamepadButtonStrings[Btn::DPAD_FACE_DOWN] = localization::resources::keybinds::controller::rsDPadDown;
        _gamepadButtonStrings[Btn::DPAD_FACE_LEFT] = localization::resources::keybinds::controller::rsDPadLeft;
        /// Face Buttons
        _gamepadButtonStrings[Btn::FACE_UP] = localization::resources::keybinds::controller::rsFaceUP;
        _gamepadButtonStrings[Btn::FACE_RIGHT] = localization::resources::keybinds::controller::rsFaceRight;
        _gamepadButtonStrings[Btn::FACE_DOWN] = localization::resources::keybinds::controller::rsFaceDown;
        _gamepadButtonStrings[Btn::FACE_LEFT] = localization::resources::keybinds::controller::rsFaceLeft;
        /// Backward buttons
        _gamepadButtonStrings[Btn::LEFT_BUMPER] = localization::resources::keybinds::controller::rsBumperLeft;
        _gamepadButtonStrings[Btn::LEFT_TRIGGER] = localization::resources::keybinds::controller::rsTriggerLeft;
        _gamepadButtonStrings[Btn::RIGHT_BUMPER] = localization::resources::keybinds::controller::rsBumperRight;
        _gamepadButtonStrings[Btn::RIGHT_TRIGGER] = localization::resources::keybinds::controller::rsTriggerRight;
        /// Middle buttons
        _gamepadButtonStrings[Btn::MIDDLE_LEFT] = localization::resources::keybinds::controller::rsMiddleLeft;
        _gamepadButtonStrings[Btn::MIDDLE] = localization::resources::keybinds::controller::rsMiddle;
        _gamepadButtonStrings[Btn::MIDDLE_RIGHT] = localization::resources::keybinds::controller::rsMiddleRight;
        /// Joystick buttons
        _gamepadButtonStrings[Btn::LEFT_THUMB] = localization::resources::keybinds::controller::rsThumbLeft;
        _gamepadButtonStrings[Btn::RIGHT_THUMB] = localization::resources::keybinds::controller::rsThumbRight;
    }

    void SettingsMenuScene::_loadGamepadKeybinds(const Section &sct)
    {
        auto &users = _world.getResource<game::resources::EngineResource>().engine->getUsers();
        _world.addEntity()
            .with<game::components::Position>(sct.pos.x + 4, sct.pos.y + 8)
            .with<game::components::Textual>(
                localization::resources::settings::rsSettingsControllerKeybinds, 20, sct.color)
            .build();

        _fillGamepadButtonStrings();

        for (size_t i = 0; i < users.getAvailableUsers(); i++)
            _loadGamepadProfile(sct, i);
    }
} // namespace game
