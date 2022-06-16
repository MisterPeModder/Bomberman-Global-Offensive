/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Menu
*/

#include "MainMenu.hpp"

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

#include "systems/Bomb.hpp"
#include "systems/ChangeCube.hpp"
#include "systems/Collision.hpp"
#include "systems/DrawingCube.hpp"
#include "systems/InputManager.hpp"
#include "systems/Movement.hpp"

#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/resource/Timer.hpp"

#include "resources/Map.hpp"

#include "logger/Logger.hpp"
#include "raylib/core/scoped.hpp"
#include "raylib/textures/Texture2D.hpp"

#include "raylib/textures/Image.hpp"

namespace Menu
{
    MainMenu::MainMenu(ecs::World &world) : _world(world) {}

    MainMenu::~MainMenu() {}

    void MainMenu::createsButtons()
    {
        std::filesystem::path logoPath = "assets/ponay.png";
        raylib::textures::Image image(logoPath, {1, 2}, raylib::core::Color::WHITE);

        _world.addEntity()
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

        _world.addEntity()
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
        _world.addEntity()
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

    void MainMenu::modulePlayerFirst()
    {
        _world.addEntity()
            .with<game::components::Position>(800.f, 100.f)
            .with<game::components::Textual>("PLAYER 1", 90, raylib::core::Color::WHITE)
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

    void MainMenu::modulePlayerSecond()
    {
        _world.addEntity()
            .with<game::components::Position>(800.f, 200.f)
            .with<game::components::Textual>("PLAYER 1", 90, raylib::core::Color::WHITE)
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

    void MainMenu::modulePlayerThird()
    {
        _world.addEntity()
            .with<game::components::Position>(800.f, 300.f)
            .with<game::components::Textual>("PLAYER 1", 90, raylib::core::Color::WHITE)
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

    void MainMenu::modulePlayerFourth()
    {
        _world.addEntity()
            .with<game::components::Position>(800.f, 400.f)
            .with<game::components::Textual>("PLAYER 1", 20, raylib::core::Color::WHITE)
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

    void MainMenu::drawFrame(const raylib::core::Camera3D &camera)
    {
        raylib::core::scoped::Drawing drawing;
        raylib::core::Window::clear();
        {
            raylib::core::scoped::Mode3D mode3D(camera);
            _world.runSystems();
        };
        raylib::core::Window::drawFPS(10, 10);
    }

    void MainMenu::setup(raylib::core::Camera3D &camera, size_t width, size_t depth)
    {
        Logger::logger.log(Logger::Severity::Information, "Start setup menu");
        /// Add world resources
        _world.addResource<game::Users>();
        _world.addResource<ecs::Timer>();
        /// Add world storages
        _world.addStorage<game::gui::Widget>();
        _world.addStorage<game::components::Bomb>();
        _world.addStorage<game::components::Position>();
        _world.addStorage<game::components::Textual>();
        _world.addStorage<game::components::Controlable>();
        /// Add world systems
        _world.addSystem<game::systems::InputManager>();

        createsButtons();
    }

} // namespace Menu