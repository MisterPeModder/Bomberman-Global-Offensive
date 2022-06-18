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
#include "game/components/Identity.hpp"
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

        if (pressedBtn == raylib::core::Gamepad::Button::MIDDLE_LEFT)
            return;
        if (pressedBtn != raylib::core::Gamepad::Button::MIDDLE_RIGHT
            && users[game::User::UserId::User1].isKeyboard()) {
            users[game::User::UserId::User1].setGamepadId(gamepadId);
        } else
            users.connectUser(gamepadId);
    }
};

struct UpdateConnected : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        auto engine = data.getResource<game::resources::EngineResource>().engine;
        auto &users = engine->getUsers();
        auto &scene = dynamic_cast<game::MainMenuScene &>(engine->getScene());
        auto firstId = scene.getFirstConnectedTextId();

        for (auto [text, id] :
            ecs::join(data.getStorage<game::components::Textual>(), data.getStorage<game::components::Identity>())) {
            if (id.id >= firstId && id.id < firstId + 4) {
                game::User::UserId userId = static_cast<game::User::UserId>(id.id - firstId);

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

namespace game
{
    MainMenuScene::MainMenuScene()
    {
        _world.addStorage<game::components::Textual>();
        _world.addSystem<game::systems::DrawText>();
        _world.addSystem<game::systems::DrawSelectedWidget>();
        _world.addSystem<game::systems::DrawRectangle>();
        _world.addSystem<DetectGamepad>();
        _world.addSystem<UpdateConnected>();

        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::DrawTexture>();

        _globalNoDraw.add<game::systems::InputManager, DetectGamepad, UpdateConnected>();
        _global2D.add<game::systems::DrawTexture>();
        _global2D.add<game::systems::DrawText>();
        _global2D.add<game::systems::DrawSelectedWidget>();
        _global2D.add<game::systems::DrawRectangle>();
        loadMainMenuScene(_world);
        loadPlayerInterface();
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
            .with<game::components::Position>(20 + 20 * static_cast<int>(id), 40)
            .with<game::components::Rectangle>()
            .with<game::components::Size>(10.f, 30.f)
            .with<game::components::Color>(color)
            .build();

        auto connectedText = _world.addEntity()
                                 .with<game::components::Position>(20 + static_cast<int>(id) * 20, 70)
                                 .with<game::components::Textual>(
                                     localization::resources::menu::rsNotConnected, 20, raylib::core::Color::RED)
                                 .with<game::components::Identity>()
                                 .build();
        if (id == 0)
            _firstUserId = _world.getStorage<components::Identity>()[connectedText.getId()].id;
    }

    void MainMenuScene::loadPlayerInterface()
    {
        for (size_t i = 0; i < 4; i++)
            loadPlayerSlot(i);

        _world.addEntity()
            .with<game::components::Controlable>(game::User::UserId::AllUsers,
                [](ecs::Entity controlable, ecs::SystemData data, const game::Users::ActionEvent &event) {
                    if (event.action == game::GameAction::DISCONNECT && event.value == 1.f) {
                        auto &users = data.getResource<game::resources::EngineResource>().engine->getUsers();
                        users.disconnectUser(event.user);
                        return true;
                    }
                    return false;
                })
            .build();
    }

    components::Identity::Id MainMenuScene::getFirstConnectedTextId() const { return _firstUserId; }
} // namespace game
