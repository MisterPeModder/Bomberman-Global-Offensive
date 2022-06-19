/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** DrawHud
*/

#include "systems/DrawHud.hpp"
#include <array>
#include "game/User.hpp"
#include "game/components/Controlable.hpp"
#include "game/components/UseCheck.hpp"
#include "game/components/items/Item.hpp"
#include "game/components/items/ItemIdentifier.hpp"
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
        ::DrawText(text.c_str(), x / 100 * raylib::core::Window::getWidth(),
            y / 100 * raylib::core::Window::getHeight(), 2, color.asRaylib());
    }

    raylib::core::Color DrawHud::whatColor(ecs::SystemData data, int id)
    {
        for (auto [player] : ecs::join(data.getStorage<game::components::Player>())) {
            switch (id) {
                case (1):
                    if (player.inventory.items[static_cast<size_t>(game::components::Item::Identifier::NoClip)] != 0)
                        return (raylib::core::Color::GREEN);
                    break;
                case (2):
                    if (player.inventory.items[static_cast<size_t>(game::components::Item::Identifier::LandMine)] != 0)
                        return (raylib::core::Color::GREEN);
                    break;
                case (3):
                    if (player.inventory.items[static_cast<size_t>(game::components::Item::Identifier::SmokeGrenade)]
                        != 0)
                        return (raylib::core::Color::GREEN);
                    break;
                case (4):
                    if (player.inventory.items[static_cast<size_t>(game::components::Item::Identifier::StunGrenade)]
                        != 0)
                        return (raylib::core::Color::GREEN);
                    break;
                case (5):
                    if (player.inventory.items[static_cast<size_t>(game::components::Item::Identifier::Punch)] != 0)
                        return (raylib::core::Color::GREEN);
                    break;

                default: break; return (raylib::core::Color::DARK_GRAY);
            }
        }

        return (raylib::core::Color::DARK_BLUE);
    }

    void DrawHud::run(ecs::SystemData data)
    {
        float x = 0;
        float y = 0;

        for (auto [player, user] :
            ecs::join(data.getStorage<game::components::Player>(), data.getStorage<game::components::Controlable>())) {
            /// x = 90 for 2nd user
            /// y = 90 for 3rnd user
            /// x = 90 & Y = 90 for 4th user
            switch (user.userId) {
                case (game::User::UserId::User1): break;
                case (game::User::UserId::User2): x = 90; break;
                case (game::User::UserId::User3): y = 90; break;
                case (game::User::UserId::User4):
                    x = 90;
                    y = 90;
                    break;
                default: break;
            }
            player.inventory.items[static_cast<size_t>(game::components::Item::Identifier::LandMine)];

            drawDataHud(1.0 + x, 3.0 + y, localization::resources::hud::rsNumberbomb, raylib::core::Color::BLUE);
            drawDataHud(5.0 + x, 3.0 + y, std::to_string(player.stats.bombLimit), raylib::core::Color::BLUE);
            drawDataHud(1.0 + x, 4.0 + y, localization::resources::hud::rsPowerBomb, raylib::core::Color::BLUE);
            drawDataHud(5.0 + x, 4.0 + y, std::to_string(player.stats.bombRange), raylib::core::Color::BLUE);
            drawDataHud(1.0 + x, 5.0 + y, localization::resources::hud::rsSpeed, raylib::core::Color::BLUE);
            drawDataHud(5.0 + x, 5.0 + y, std::to_string(player.stats.speed), raylib::core::Color::BLUE);

            drawDataHud(1.0 + x, 6.0 + y, localization::resources::hud::rsActivable, raylib::core::Color::GREEN);
            drawDataHud(1.0 + x, 7.0 + y, localization::resources::hud::rsNoclip, whatColor(data, 1));
            drawDataHud(1.0 + x, 8.0 + y, localization::resources::hud::rsLandMine, whatColor(data, 2));
            drawDataHud(1.0 + x, 9.0 + y, localization::resources::hud::rsSmokeGrenade, whatColor(data, 3));
            drawDataHud(1.0 + x, 10.0 + y, localization::resources::hud::rsStunGrenade, whatColor(data, 4));
            drawDataHud(1.0 + x, 11.0 + y, localization::resources::hud::rsPunch, whatColor(data, 5));
        }
    }
} // namespace game::systems
