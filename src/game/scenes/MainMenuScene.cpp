/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** MainMenuScene
*/

#include "MainMenuScene.hpp"

#include "util/util.hpp"

#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/RotationAngle.hpp"
#include "game/components/RotationAxis.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/systems/Model.hpp"

#include "game/Users.hpp"
#include "game/components/Bomb.hpp"
#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Image.hpp"
#include "game/components/Position.hpp"
#include "game/components/Textual.hpp"
#include "game/components/Texture2D.hpp"
#include "game/gui/components/Widget.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"

#include "logger/Logger.hpp"

static void loadMainMenuScene(ecs::World &world)
{
    static const std::filesystem::path testModelPath = util::makePath("assets", "models", "player", "raylibguy.iqm");

    world.addSystem<game::systems::DrawModel>();
    world.addStorage<game::components::Scale>();

    world.addEntity()
        .with<game::components::Model>(testModelPath)
        .with<game::components::Position>(0, -2, 0)
        .with<game::components::Size>(0.5f, 0.5f, 0.5f)
        .with<game::components::RotationAngle>(-90)
        .with<game::components::RotationAxis>(1, 0, 0)
        .with<game::components::Color>(raylib::core::Color::GREEN)
        .build();

    std::filesystem::path logoPath = "assets/ponay.png";
    raylib::textures::Image image(logoPath, {1, 2}, raylib::core::Color::WHITE);

    world.addEntity()
        .with<game::components::Position>(50.f, 50.f)
        .with<game::components::Textual>("PLAY", 20, raylib::core::Color::WHITE)
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
        .with<game::components::Position>(100.f, 50.f)
        .with<game::components::Textual>("OPTION", 20, raylib::core::Color::WHITE)
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
        .with<game::components::Position>(50.f, 50.f)
        .with<game::components::Textual>("QUIT", 20, raylib::core::Color::WHITE)
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
}

namespace game
{
    MainMenuScene::MainMenuScene() { loadMainMenuScene(_world); }
} // namespace game
