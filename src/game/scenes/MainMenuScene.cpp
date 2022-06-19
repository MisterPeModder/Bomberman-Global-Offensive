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
                users.connectUser(gamepadId, dynamic_cast<game::MainMenuScene &>(engine->getScene()).getUnusedSkin());
                dynamic_cast<game::MainMenuScene &>(engine->getScene()).updateConnectedTexts();
                dynamic_cast<game::MainMenuScene &>(engine->getScene()).updateSkinTexts();
            }
        }
    };

    MainMenuScene::MainMenuScene()
    {
        for (int i = 0; i < User::USER_SKINS::UNKNOWN; i++) {
            _availableSkins.push(User::USER_SKINS(i));
        }

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

                    if (engine->getUsers().getAvailableUsers() < 2)
                        return;
                    engine->setScene<GameScene>(Game::Parameters(engine->getUsers().prepareSkinParameters(),
                        (nbUsers < 2) ? 2 : engine->getUsers().getAvailableUsers()));
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

        // Skin Text
        auto builder = _world.addEntity();
        (void)builder.with<components::Position>(20 + static_cast<int>(id) * 20, 75)
            .with<components::Identity>()
            .with<components::Controlable>(User::UserId::AllUsers,
                [this](ecs::Entity controlable, ecs::SystemData data, const Users::ActionEvent &event) {
                    (void)controlable;
                    if (event.action != GameAction::NEXT_ACTIVABLE || event.value != 1.f)
                        return false;

                    auto &user = data.getResource<game::resources::EngineResource>().engine->getUsers()[event.user];
                    _availableSkins.push(user.getSkin());
                    user.setSkin(_availableSkins.front());
                    _availableSkins.pop();
                    updateSkinTexts();
                    return true;
                });
        if (id == 0) {
            (void)builder.with<components::Textual>(
                userSkinToRessourceString(_availableSkins.front()), 20, raylib::core::Color::WHITE);
            _availableSkins.pop();
        } else {
            (void)builder.with<components::Textual>(
                userSkinToRessourceString(User::USER_SKINS::UNKNOWN), 20, raylib::core::Color::WHITE);
        }
        auto skinText = builder.build();
        _skinTexts[id] = _world.getStorage<components::Identity>()[skinText.getId()].id;

        auto connectedText =
            _world.addEntity()
                .with<components::Position>(20 + static_cast<int>(id) * 20, 70)
                .with<components::Textual>(localization::resources::menu::rsNotConnected, 20, raylib::core::Color::RED)
                .with<components::Identity>()
                .build();

        _connectedTexts[id] = _world.getStorage<components::Identity>()[connectedText.getId()].id;
        if (id == 0) {
            auto &text = _world.getStorage<components::Textual>()[connectedText.getId()];
            text.text = localization::resources::menu::rsConnected;
            text.color = raylib::core::Color::GREEN;
        }
    }

    localization::ResourceString MainMenuScene::userSkinToRessourceString(User::USER_SKINS skin)
    {
        switch (skin) {
            case User::USER_SKINS::TERRORIST_1: return localization::resources::textures::rsTerroristOne;
            case User::USER_SKINS::TERRORIST_2: return localization::resources::textures::rsTerroristTwo;
            case User::USER_SKINS::COUNTER_TERRORIST_1: return localization::resources::textures::rsCounterTerroristOne;
            case User::USER_SKINS::COUNTER_TERRORIST_2: return localization::resources::textures::rsCounterTerroristTwo;
            case User::USER_SKINS::NO_SENSE: return localization::resources::textures::rsNoSense;
            case User::USER_SKINS::RAINBOW: return localization::resources::textures::rsRainbow;
            default: return localization::resources::textures::rsUnknown;
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
                        auto &lusers = data.getResource<resources::EngineResource>().engine->getUsers();
                        User::USER_SKINS temp = lusers[event.user].getSkin();
                        if (lusers.disconnectUser(event.user)) {
                            _availableSkins.push(temp);
                            updateSkinTexts();
                        };
                        updateConnectedTexts();
                        return true;
                    }
                    return false;
                })
            .build();
    }

    void MainMenuScene::updateSkinTexts()
    {
        auto engine = _world.getResource<game::resources::EngineResource>().engine;
        auto &users = engine->getUsers();

        for (auto [text, id] :
            ecs::join(_world.getStorage<components::Textual>(), _world.getStorage<components::Identity>())) {
            for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++) {
                if (_skinTexts[i] != id.id)
                    continue;
                User::UserId userId = static_cast<User::UserId>(i);
                text.text = userSkinToRessourceString(users[userId].getSkin());
            }
        }
    }

    void MainMenuScene::updateConnectedTexts()
    {
        auto engine = _world.getResource<game::resources::EngineResource>().engine;
        auto &users = engine->getUsers();

        for (auto [text, id] :
            ecs::join(_world.getStorage<components::Textual>(), _world.getStorage<components::Identity>())) {
            for (size_t i = 0; i < static_cast<size_t>(User::UserId::UserCount); i++) {
                if (_connectedTexts[i] != id.id)
                    continue;
                User::UserId userId = static_cast<User::UserId>(i);

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

    User::USER_SKINS MainMenuScene::getUnusedSkin()
    {
        User::USER_SKINS skin = _availableSkins.front();

        _availableSkins.pop();
        return skin;
    }

} // namespace game
