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
#include "raylib/textures/Image.hpp"

namespace Menu
{
    MainMenu::MainMenu() {}
    MainMenu::~MainMenu() {}

    void MainMenu::createsButtons(ecs::World &world)
    {
       /*  struct Image : public ecs::Component, public raylib::textures::Image {
            Image(const std::filesystem::path &fileName, raylib::core::Vector2 position = {},
                const raylib::core::Color &color = raylib::core::Color::DEFAULT_COLOR)
                : raylib::textures::Image(fileName)
            {
            }
        };
        world.addEntity()
            .with<game::Position>(0.f, 0.f)
            .with<game::Color>
            .with<Image>("assets/logo.jpg")
            .build(); */

        world.addEntity()
            .with<game::Position>(0.f, 0.f)
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

} // namespace Menu