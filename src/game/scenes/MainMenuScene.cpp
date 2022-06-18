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
#include "ecs/resource/Timer.hpp"

#include "util/util.hpp"

#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Image.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/components/Textual.hpp"
#include "game/components/Texture2D.hpp"

#include "game/scenes/IScene.hpp"
#include "game/scenes/SettingsMenuScene.hpp"
#include "raylib/core/Window.hpp"

#include "game/Game.hpp"
#include "game/Users.hpp"
#include "game/scenes/GameScene.hpp"

#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/scenes/SettingsMenuScene.hpp"
#include "game/systems/DrawSelectedWidget.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/DrawTexture.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"
#include "game/systems/Rectangle.hpp"

#include "game/resources/Engine.hpp"

#include "logger/Logger.hpp"

#include "localization/Localization.hpp"
#include "localization/Resources.hpp"

#include "game/Engine.hpp"
#include "raylib/core/Window.hpp"

struct DetectGamepad : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        auto &users = data.getResource<game::resources::EngineResource>().engine->getUsers();

        int gamepadId = users.getJoiningGamepad();
        if (gamepadId == -1)
            return;
        raylib::core::Gamepad::Button pressedBtn = raylib::core::Gamepad::getButtonPressed();

        if (pressedBtn != raylib::core::Gamepad::Button::MIDDLE_RIGHT
            && users[game::User::UserId::User1].isKeyboard()) {
            users[game::User::UserId::User1].setGamepadId(gamepadId);
        } else
            users.connectUser(gamepadId);
    }
};

static void loadMainMenuScene(ecs::World &world)
{
    static const std::filesystem::path logoPath = util::makePath("assets", "icon.png");
    raylib::textures::Image image(logoPath, {1, 2}, raylib::core::Color::WHITE);

    world.addEntity()
        .with<game::components::Position>(2, 12)
        .with<game::components::Textual>(localization::resources::menu::rsMenuPlay, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::MainMenuScene::PLAY, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, game::MainMenuScene::OPTION, true)
        .with<game::gui::Clickable>(
            [&world](ecs::Entity) {
                auto &engine = world.getResource<game::resources::EngineResource>().engine;

                engine->setScene<game::GameScene>(game::Game::Parameters(engine->getUsers().getAvailableUsers()));
                Logger::logger.log(Logger::Severity::Debug, "go to game");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::BLUE;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(2, 20)
        .with<game::components::Textual>(localization::resources::menu::rsMenuOption, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::MainMenuScene::OPTION, game::gui::Widget::NullTag,
            game::MainMenuScene::JOIN_SLOT_ONE, game::MainMenuScene::PLAY, game::MainMenuScene::LOGOUT)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            world.getResource<game::resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
            Logger::logger.log(Logger::Severity::Debug, "go to option");
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(2, 90)
        .with<game::components::Textual>(localization::resources::menu::rsMenuQuit, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::MainMenuScene::LOGOUT, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::MainMenuScene::OPTION, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>([](ecs::Entity) {
            raylib::core::Window::setShouldClose();
            Logger::logger.log(Logger::Severity::Debug, "close game");
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(0, 0)
        .with<game::components::Texture2D>(logoPath)
        .with<game::components::Scale>(0.4f)
        .with<game::components::RotationAngle>(0.f)
        .with<game::components::Color>(255, 255, 255, 200)
        .build();
}

static void loadPlayerInterface(ecs::World &world)
{
    // player1
    world.addEntity()
        .with<game::components::Position>(20, 40)
        .with<game::components::Rectangle>()
        .with<game::components::Size>(10.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::BLUE)
        .build();

    // world.addEntity()
    //     .with<game::components::Position>(20, 70)
    //     .with<game::components::Textual>(localization::resources::menu::rsNotConnected, 20, raylib::core::Color::RED)
    //     .with<game::components::Controlable>(game::User::UserId::AllUsers,
    //         [](ecs::Entity controlable, ecs::SystemData data, const game::Users::ActionEvent &event) {
    //             if (event.action == game::GameAction::DISCONNECT && event.value == 1.f) {
    //                 auto &users = data.getResource<game::resources::EngineResource>().engine->getUsers();
    //                 std::cout << "User " << static_cast<size_t>(event.user) << " disconnected " << std::endl;
    //                 users.disconnectUser(event.user);
    //             }

    //             return false;
    //         })
    //     .build();
    // player2
    world.addEntity()
        .with<game::components::Position>(40, 40)
        .with<game::components::Rectangle>()
        .with<game::components::Size>(10.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::RED)
        .build();

    // player3
    world.addEntity()
        .with<game::components::Position>(60, 40)
        .with<game::components::Rectangle>()
        .with<game::components::Size>(10.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::GREEN)
        .build();

    // player4
    world.addEntity()
        .with<game::components::Position>(80, 40)
        .with<game::components::Rectangle>()
        .with<game::components::Size>(10.f, 30.f)
        .with<game::components::Color>(raylib::core::Color::PURPLE)
        .build();
}

namespace game
{
    MainMenuScene::MainMenuScene()
    {
        _world.addStorage<game::components::Textual>();
        _world.addSystem<game::systems::DrawText>();
        _world.addSystem<game::systems::DrawSelectedWidget>();
        _world.addSystem<game::systems::DrawRectangle>();
        _world.addSystem<DetectGamepad>();

        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::DrawTexture>();

        _globalNoDraw.add<game::systems::InputManager, DetectGamepad>();
        _global2D.add<game::systems::DrawTexture>();
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::DrawSelectedWidget>();
        _global2D.add<game::systems::DrawRectangle>();
        loadMainMenuScene(_world);
        loadPlayerInterface(_world);
    }
} // namespace game
