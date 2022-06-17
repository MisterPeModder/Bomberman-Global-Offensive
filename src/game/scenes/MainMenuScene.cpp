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
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/components/Textual.hpp"
#include "game/components/Texture2D.hpp"

#include "game/scenes/IScene.hpp"
#include "game/scenes/SettingsMenuScene.hpp"

#include "game/Game.hpp"
#include "game/Users.hpp"
#include "game/scenes/GameScene.hpp"

#include "game/gui/components/Clickable.hpp"
#include "game/gui/components/Widget.hpp"

#include "game/scenes/SettingsMenuScene.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/DrawTexture.hpp"
#include "game/systems/InputManager.hpp"
#include "game/systems/Model.hpp"

#include "game/resources/Engine.hpp"

#include "logger/Logger.hpp"

#include "localization/Localization.hpp"
#include "localization/Resources.hpp"

#include "game/Engine.hpp"
#include "raylib/core/Window.hpp"

static void loadMainMenuScene(ecs::World &world)
{
    static const std::filesystem::path logoPath = util::makePath("assets", "icon.png");
    raylib::textures::Image image(logoPath, {1, 2}, raylib::core::Color::WHITE);

    world.addEntity()
        .with<game::components::Position>(0, 10)
        .with<game::components::Textual>(localization::resources::menu::rsMenuPlay, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::MainMenuScene::PLAY, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, game::MainMenuScene::OPTION, true)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            world.getResource<game::resources::EngineResource>().engine->setScene<game::GameScene>();
            Logger::logger.log(Logger::Severity::Debug, "go to game");
        })
        .build();

    world.addEntity()
        .with<game::components::Position>(0, 20)
        .with<game::components::Textual>(localization::resources::menu::rsMenuOption, 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::MainMenuScene::OPTION, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::MainMenuScene::PLAY, game::MainMenuScene::LOGOUT)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            world.getResource<game::resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
            Logger::logger.log(Logger::Severity::Debug, "go to option");
        })
        .build();
    world.addEntity()
        .with<game::components::Position>(0, 90)
        .with<game::components::Textual>(localization::resources::menu::rsMenuQuit, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(game::MainMenuScene::LOGOUT, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::MainMenuScene::OPTION, game::gui::Widget::NullTag)
        .with<game::gui::Clickable>([&world](ecs::Entity) {
            raylib::core::Window::close();
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
        _world.addResource<game::Users>();
        _world.addStorage<game::components::Textual>();
        _world.addSystem<game::systems::DrawText>();

        _world.addSystem<game::systems::InputManager>();
        _world.addSystem<game::systems::DrawTexture>();

        _globalNoDraw.add<game::systems::InputManager>();
        _global2D.add<game::systems::DrawTexture>();
        _global2D.add<game::systems::DrawText>();
        loadMainMenuScene(_world);
    }
} // namespace game
