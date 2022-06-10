/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Menu
*/

#include "MainMenu.hpp"
#include "game/Users.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/Position.hpp"
#include "game/components/Textual.hpp"
#include "game/gui/components/Rectangle.hpp"
#include "game/systems/DrawText.hpp"
#include "game/systems/InputManager.hpp"
#include "logger/Logger.hpp"

namespace Menu
{
    MainMenu::MainMenu()
    {
        menu.addResource<game::Users>();
        menu.addSystem<game::DrawText>();
        menu.addSystem<game::InputManager>();
    }
    MainMenu::~MainMenu() {}

    void MainMenu::createsButtons()
    {
        game::Rectangle test({50, 50}, {1, 1}, raylib::core::Color::RED);
        menu.addEntity()
            .with<game::Position>(50.f, 50.f)
            .with<game::Textual>("PLAY", 20, raylib::core::Color::WHITE)
            .with<game::Controlable>(game::User::UserId::User1,
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

    void MainMenu::run() { menu.runSystems(); }

} // namespace Menu