/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"

#include "ecs/resource/Resource.hpp"

#include "util/util.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/KeybindIntercepter.hpp"
#include "game/components/KeyboardInput.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/Size.hpp"
#include "game/components/Textual.hpp"
#include "game/components/Texture2D.hpp"
#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/systems/DrawSelectedWidget.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/DrawTexture.hpp"
#include "game/systems/DrawTextureBackground.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "game/systems/Rectangle.hpp"

#include "game/resources/Engine.hpp"

#include "game/scenes/GameScene.hpp"
#include "game/scenes/IScene.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include "raylib/core/Window.hpp"

#include "game/Engine.hpp"
#include "game/Game.hpp"
#include "game/Users.hpp"

#include "localization/Localization.hpp"
#include "localization/Resources.hpp"
#include "logger/Logger.hpp"

namespace game
{
    struct DetectGamepad : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto engine = data.getResource<game::resources::EngineResource>().engine;
            auto &users = engine->getUsers();

            int gamepadId = users.getJoiningGamepad();
            if (gamepadId == -1)
                return;
            raylib::core::Gamepad::Button pressedBtn = raylib::core::Gamepad::getButtonPressed();

            if (pressedBtn == raylib::core::Gamepad::Button::MIDDLE_LEFT)
                return;
            if (pressedBtn != raylib::core::Gamepad::Button::MIDDLE_RIGHT
                && users[game::User::UserId::User1].isKeyboard()) {
                users[game::User::UserId::User1].setGamepadId(gamepadId);
                Logger::logger.log(Logger::Severity::Information, "User 1 switched to gamepad mode.");
            } else {
                users.connectUser(gamepadId);
                dynamic_cast<game::MainMenuScene &>(engine->getScene()).updateConnectedTexts();
            }
        }
    };

    MainMenuScene::MainMenuScene()
    {
        _world.addStorage<components::Textual>();
        _world.addStorage<components::KeyboardInput>();
        _world.addSystem<systems::DrawText>();
        _world.addSystem<systems::DrawSelectedWidget>();
        _world.addSystem<systems::DrawRectangle>();
        _world.addSystem<DetectGamepad>();
        _world.addStorage<game::components::KeybindIntercepter>();

        _world.addSystem<systems::InputManager>();
        _world.addSystem<systems::DrawTexture>();
        _world.addSystem<systems::DrawTextureBackground>();

        _globalNoDraw.add<systems::InputManager, DetectGamepad>();
        _global2D.add<systems::DrawTexture>();
        _global2D.add<systems::DrawText>();
        _global2D.add<systems::DrawSelectedWidget>();
        _global2D.add<systems::DrawRectangle>();
        _background2D.add<systems::DrawTextureBackground>();

        static const std::filesystem::path backgroundPath =
            util::makePath("assets", "images", "background", "main-menu-background.png");

        _world.addEntity()
            .with<game::components::Texture2D>(backgroundPath)
            .with<game::components::Position>(0.f, 0.f)
            .with<game::components::Scale>(1.f)
            .with<game::components::RotationAngle>(0.f)
            .with<game::components::Color>(255, 255, 255, 255)
            .build();

        loadLeftButtons();
        loadPlayerInterface();
    }

    void MainMenuScene::loadLeftButtons()
    {
        const std::filesystem::path logoPath = util::makePath("assets", "icon.png");

        //// Play
        _world.addEntity()
            .with<components::Position>(2, 12)
            .with<components::Textual>(localization::resources::menu::rsMenuPlay, 20, raylib::core::Color::WHITE)
            .with<components::Controlable>(User::UserId::User1)
            .with<gui::Widget>(MainMenuScene::PLAY, gui::Widget::NullTag, gui::Widget::NullTag, gui::Widget::NullTag,
                MainMenuScene::SETTINGS, true)
            .with<gui::Clickable>(
                [this](ecs::Entity) {
                    auto &engine = _world.getResource<resources::EngineResource>().engine;
                    size_t nbUsers = engine->getUsers().getAvailableUsers();

                    engine->setScene<GameScene>(
                        Game::Parameters((nbUsers < 2) ? 2 : engine->getUsers().getAvailableUsers()));
                },
                [this](ecs::Entity btn, gui::Clickable::State state) {
                    _world.getStorage<components::Textual>()[btn.getId()].color =
                        (state == gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                  : raylib::core::Color::BLUE;
                })
            .build();

        /// Settings
        _world.addEntity()
            .with<components::Position>(2, 20)
            .with<components::Textual>(localization::resources::menu::rsMenuSettings, 20, raylib::core::Color::WHITE)
            .with<components::Controlable>(User::UserId::User1)
            .with<gui::Widget>(MainMenuScene::SETTINGS, gui::Widget::NullTag, MainMenuScene::JOIN_SLOT_ONE,
                MainMenuScene::PLAY, MainMenuScene::LOGOUT)
            .with<gui::Clickable>([this](ecs::Entity) {
                _world.getResource<resources::EngineResource>().engine->setScene<SettingsMenuScene>();
            })
            .build();

#ifndef __EMSCRIPTEN__
        /// Quit
        _world.addEntity()
            .with<components::Position>(2, 90)
            .with<components::Textual>(localization::resources::menu::rsMenuQuit, 20, raylib::core::Color::WHITE)
            .with<components::Controlable>(User::UserId::User1)
            .with<gui::Widget>(MainMenuScene::LOGOUT, gui::Widget::NullTag, gui::Widget::NullTag,
                MainMenuScene::SETTINGS, gui::Widget::NullTag)
            .with<gui::Clickable>([](ecs::Entity) { raylib::core::Window::setShouldClose(); })
            .build();
#endif

        /// Logo
        _world.addEntity()
            .with<components::Position>(0, 0)
            .with<components::Texture2D>(logoPath)
            .with<components::Scale>(0.4f)
            .with<components::RotationAngle>(0.f)
            .with<components::Color>(255, 255, 255, 200)
            .build();
    }

    void MainMenuScene::loadPlayerSlot(size_t id)
    {
        raylib::core::Color color;

        switch (id) {
            case 0: color = raylib::core::Color::BLUE; break;
            case 1: color = raylib::core::Color::RED; break;
            case 2: color = raylib::core::Color::GREEN; break;
            default: color = raylib::core::Color::PURPLE; break;
        }

        // player Rect
        _world.addEntity()
            .with<components::Position>(20 + 20 * static_cast<int>(id), 40)
            .with<components::Rectangle>()
            .with<components::Size>(10.f, 30.f)
            .with<components::Color>(color)
            .build();

        auto connectedText =
            _world.addEntity()
                .with<components::Position>(20 + static_cast<int>(id) * 20, 70)
                .with<components::Textual>(localization::resources::menu::rsNotConnected, 20, raylib::core::Color::RED)
                .with<components::Identity>()
                .build();
        if (id == 0) {
            _firstUserId = _world.getStorage<components::Identity>()[connectedText.getId()].id;
            auto &text = _world.getStorage<components::Textual>()[connectedText.getId()];
            text.text = localization::resources::menu::rsConnected;
            text.color = raylib::core::Color::GREEN;
        }
    }

    void MainMenuScene::loadPlayerInterface()
    {
        for (size_t i = 0; i < 4; i++)
            loadPlayerSlot(i);

        _world.addEntity()
            .with<components::Controlable>(User::UserId::AllUsers,
                [this](ecs::Entity controlable, ecs::SystemData data, const Users::ActionEvent &event) {
                    (void)controlable;
                    if (event.action == GameAction::DISCONNECT && event.value == 1.f) {
                        auto &users = data.getResource<resources::EngineResource>().engine->getUsers();
                        users.disconnectUser(event.user);
                        updateConnectedTexts();
                        return true;
                    }
                    return false;
                })
            .build();
    }

    void MainMenuScene::updateConnectedTexts()
    {
        auto engine = _world.getResource<game::resources::EngineResource>().engine;
        auto &users = engine->getUsers();

        for (auto [text, id] :
            ecs::join(_world.getStorage<components::Textual>(), _world.getStorage<components::Identity>())) {
            if (id.id >= _firstUserId && id.id < _firstUserId + 4) {
                User::UserId userId = static_cast<User::UserId>(id.id - _firstUserId);

                if (users[userId].isAvailable()) {
                    text.text = localization::resources::menu::rsConnected;
                    text.color = raylib::core::Color::GREEN;
                } else {
                    text.text = localization::resources::menu::rsNotConnected;
                    text.color = raylib::core::Color::RED;
                }
            }
        }
    }

} // namespace game
