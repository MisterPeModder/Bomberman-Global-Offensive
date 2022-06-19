/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** DrawHud
*/

#include "systems/DrawHud.hpp"
#include "game/User.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/UseCheck.hpp"
#include "localization/Localization.hpp"
#include "localization/Resources.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Window.hpp"
#include "raylib/text/text.hpp"
#include "systems/DrawText.hpp"
extern "C"
{
#include "raylib.h"
}

namespace game::systems
{
    void DrawHud::drawDataHud(float x, float y, std::string text, raylib::core::Color color)
    {
        Logger::logger.log(Logger::Severity::Information, "Draw my hud");
        ::DrawText(text.c_str(), x / 100 * raylib::core::Window::getWidth(),
            y / 100 * raylib::core::Window::getHeight(), 2, color.asRaylib());
    }
    void DrawHud::run(ecs::SystemData data)
    {
        float x = 0;
        float y = 0;

        Logger::logger.log(Logger::Severity::Information, "enter in hud draw");
        for (auto [player, user] :
            ecs::join(data.getStorage<game::components::Player>(), data.getStorage<game::components::Controlable>())) {
            // game::components::Textual nbbom(std::to_string(hud.nbBomb), 20, raylib::core::Color::WHITE);
            /// x = 90 for 2nd user
            /// y = 90 for 3rnd user
            /// x = 90 & Y = 90 for 4th user
            switch (user.userId) {
                case (game::User::UserId::User1):
                    break;
                case (game::User::UserId::User2): x = 90; break;
                case (game::User::UserId::User3): 
                    y = 90;
                    break;
                case (game::User::UserId::User4):
                    x = 90;
                    y = 90;
                    break;
                default: break;
            }
            drawDataHud(1.0 + x, 3.0 + y, localization::resources::hud::rsNumberbomb, raylib::core::Color::BLUE);
            drawDataHud(5.0 + x, 3.0 + y, std::to_string(player.stats.bombLimit), raylib::core::Color::BLUE);
            drawDataHud(1.0 + x, 4.0 + y, localization::resources::hud::rsPowerBomb, raylib::core::Color::BLUE);
            drawDataHud(5.0 + x, 4.0 + y, std::to_string(player.stats.bombRange), raylib::core::Color::BLUE);
            drawDataHud(1.0 + x, 5.0 + y, localization::resources::hud::rsSpeed, raylib::core::Color::BLUE);
            drawDataHud(5.0 + x, 5.0 + y, std::to_string(player.stats.speed), raylib::core::Color::BLUE);
            // drawDataHud(1.0, 3.0, localization::resources::hud::rsNumberbomb, raylib::core::Color::BLUE);
            // drawDataHud(5.0, 3.0, std::to_string(player.stats.bombLimit), raylib::core::Color::BLUE);
            // drawDataHud(1.0, 4.0, localization::resources::hud::rsPowerBomb, raylib::core::Color::BLUE);
            // drawDataHud(5.0, 4.0, std::to_string(player.stats.bombRange), raylib::core::Color::BLUE);
            // drawDataHud(1.0, 5.0, localization::resources::hud::rsSpeed, raylib::core::Color::BLUE);
            // drawDataHud(5.0, 5.0, std::to_string(player.stats.speed), raylib::core::Color::BLUE);
        }
    }
} // namespace game::systems
