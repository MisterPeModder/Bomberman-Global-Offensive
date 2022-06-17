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

#include "game/Users.hpp"

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

/////////////////////////////////////////////////

static void loadMainMenuScene(ecs::World &world)
{
    std::filesystem::path logoPath = util::makePath("assets", "icon.png");
    raylib::textures::Image image(logoPath, {1, 2}, raylib::core::Color::WHITE);

    world.addEntity()
        .with<game::components::Position>(0.f, 100.f)
        .with<game::components::Textual>(localization::resources::menu::rsMenuPlay, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1,
            [](ecs::Entity self, ecs::SystemData data, const game::Users::ActionEvent &event) {
                (void)self;
                (void)data;
                (void)event;
                Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                    writer << "PLAYED! " << event.value << ", " << static_cast<size_t>(event.action);
                });
                return false;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(0.f, 130.f)
        .with<game::components::Textual>(localization::resources::menu::rsMenuOption, 20, raylib::core::Color::RED)
        .with<game::components::Controlable>(game::User::UserId::User1,
            [](ecs::Entity self, ecs::SystemData data, const game::Users::ActionEvent &event) {
                (void)self;
                (void)data;
                (void)event;
                Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                    writer << "PLAYED! " << event.value << ", " << static_cast<size_t>(event.action);
                });
                return false;
            })
        /* .with<game::gui::Clickable>([&world](ecs::Entity) {
            world.getResource<game::resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();
            Logger::logger.log(Logger::Severity::Debug, "switch to menu option");
        }) */
        .with<game::gui::Clickable>(
            [](ecs::Entity) {
                world.getResource<resources::EngineResource>().engine->setScene<game::SettingsMenuScene>();

                Logger::logger.log(Logger::Severity::Debug, "Toggled fullscreen");
            },
            [&](ecs::Entity btn, game::gui::Clickable::State state) {
                world.getStorage<game::components::Textual>()[btn.getId()].color =
                    (state == game::gui::Clickable::State::Pressed) ? raylib::core::Color::YELLOW
                                                                    : raylib::core::Color::RED;
            })
        .build();
    world.addEntity()
        .with<game::components::Position>(0.f, 700.f)
        .with<game::components::Textual>(localization::resources::menu::rsMenuQuit, 20, raylib::core::Color::WHITE)
        .with<game::components::Controlable>(game::User::UserId::User1,
            [](ecs::Entity self, ecs::SystemData data, const game::Users::ActionEvent &event) {
                (void)self;
                (void)data;
                (void)event;
                Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                    writer << "PLAYED! " << event.value << ", " << static_cast<size_t>(event.action);
                });
                return false;
            })
        .build();

    world.addEntity()
        .with<game::components::Position>(0.f, 0.f)
        .with<game::components::Texture2D>(logoPath)
        .with<game::components::Scale>(0.4f)
        .with<game::components::RotationAngle>(0.f)
        .with<game::components::Color>(255, 255, 255, 200)
        .with<game::components::Controlable>(game::User::UserId::User1)
        .with<game::gui::Widget>(0, game::gui::Widget::NullTag, game::gui::Widget::NullTag, game::gui::Widget::NullTag,
            game::gui::Widget::NullTag, true)
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
