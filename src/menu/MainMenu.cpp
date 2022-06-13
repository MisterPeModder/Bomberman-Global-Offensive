/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Menu
*/

#include "MainMenu.hpp"
#include "game/Users.hpp"
#include "game/components/Color.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Image.hpp"
#include "game/components/Position.hpp"
#include "game/components/Textual.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"

#include "raylib/core/scoped.hpp"
#include "logger/Logger.hpp"

namespace Menu
{
    MainMenu::MainMenu(ecs::World &world) : _world(world) {}

    MainMenu::~MainMenu() {}

    void MainMenu::createsButtons()
    {
        /* std::filesystem::path logoPath = "assets/ponay.png";

        world.addEntity()
            .with<game::components::Position>(0.f, 0.f)
            .with<game::Color>(raylib::core::Color::GRAY)
            .with<game::Image>(logoPath)
            .build(); */

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

} // namespace Menu