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
    void DrawHud::drawBorder(float x, float y)
    {
        int getWidth = 100 * raylib::core::Window::getWidth();
        int getHeight = 100 * raylib::core::Window::getHeight();

        ::DrawRectangleLines(
            x / getWidth, y / getHeight, 5 / getWidth, 15 / getHeight, raylib::core::Color::PURPLE.asRaylib());
    }

    void DrawHud::drawDataHud(float x, float y, std::string text, raylib::core::Color color)
    {
        ::DrawText(text.c_str(), x / 100 * raylib::core::Window::getWidth(),
            y / 100 * raylib::core::Window::getHeight(), 15, color.asRaylib());
    }

    raylib::core::Color DrawHud::whatColor(components::Player::Inventory inv, int id, float x, float y)
    {
        size_t occurence = 0;

        switch (id) {
            case (1):
                occurence = inv.items[static_cast<size_t>(game::components::Item::Identifier::NoClip)];
                if (inv.selected == game::components::Item::Identifier::NoClip) {
                    drawDataHud(11.f + x, 12.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::RED);
                }
                if (occurence != 0) {
                    drawDataHud(11.f + x, 12.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::GREEN);
                }
                break;
            case (2):
                occurence = inv.items[static_cast<size_t>(game::components::Item::Identifier::LandMine)];
                if (inv.selected == game::components::Item::Identifier::LandMine) {
                    drawDataHud(11.f + x, 14.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::RED);
                }
                if (occurence != 0) {
                    drawDataHud(11.f + x, 14.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::GREEN);
                }
                break;
            case (3):
                occurence = inv.items[static_cast<size_t>(game::components::Item::Identifier::SmokeGrenade)];
                if (inv.selected == game::components::Item::Identifier::SmokeGrenade) {
                    drawDataHud(11.f + x, 16.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::RED);
                }
                if (occurence != 0) {
                    drawDataHud(11.f + x, 16.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::GREEN);
                }
                break;
            case (4):
                occurence = inv.items[static_cast<size_t>(game::components::Item::Identifier::StunGrenade)];
                if (inv.selected == game::components::Item::Identifier::StunGrenade) {
                    drawDataHud(11.f + x, 18.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::RED);
                }
                if (occurence != 0) {
                    drawDataHud(11.f + x, 18.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::GREEN);
                }
                break;
            case (5):
                occurence = inv.items[static_cast<size_t>(game::components::Item::Identifier::Punch)];
                if (inv.selected == game::components::Item::Identifier::Punch) {
                    drawDataHud(11.f + x, 20.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::RED);
                }
                if (occurence != 0) {
                    drawDataHud(11.f + x, 20.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::GREEN);
                }
                break;
            case (6):
                occurence = inv.items[static_cast<size_t>(game::components::Item::Identifier::KickShoes)];
                if (inv.selected == game::components::Item::Identifier::KickShoes) {
                    drawDataHud(11.f + x, 22.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::RED);
                }
                if (occurence != 0) {
                    drawDataHud(11.f + x, 22.f + y, std::to_string(occurence), raylib::core::Color::RED);
                    return (raylib::core::Color::GREEN);
                }
                break;

            default: break; return (raylib::core::Color::DARK_GRAY);
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
                case (game::User::UserId::User2): x = 83; break;
                case (game::User::UserId::User3): y = 90; break;
                case (game::User::UserId::User4):
                    x = 83;
                    y = 90;
                    break;
                default: break;
            }

            drawBorder(x, y);

            drawDataHud(1.f + x, 3.f + y, localization::resources::hud::rsBombs, raylib::core::Color::BLUE);
            drawDataHud(11.f + x, 3.f + y, std::to_string(player.stats.bombLimit), raylib::core::Color::BLUE);
            drawDataHud(1.f + x, 5.f + y, localization::resources::hud::rsPower, raylib::core::Color::BLUE);
            drawDataHud(11.f + x, 5.f + y, std::to_string(player.stats.bombRange), raylib::core::Color::BLUE);
            drawDataHud(1.f + x, 7.f + y, localization::resources::hud::rsSpeed, raylib::core::Color::BLUE);
            drawDataHud(11.f + x, 7.f + y, std::to_string(player.stats.speed), raylib::core::Color::BLUE);

            drawDataHud(1.f + x, 10.f + y, localization::resources::hud::rsInventory, raylib::core::Color::PURPLE);
            drawDataHud(
                1.f + x, 12.f + y, localization::resources::hud::rsWallPass, whatColor(player.inventory, 1, x, y));
            drawDataHud(
                1.f + x, 14 + y, localization::resources::hud::rsLandMine, whatColor(player.inventory, 2, x, y));
            drawDataHud(
                1.f + x, 16 + y, localization::resources::hud::rsSmokeGrenade, whatColor(player.inventory, 3, x, y));
            drawDataHud(
                1.f + x, 18.f + y, localization::resources::hud::rsStunGrenade, whatColor(player.inventory, 4, x, y));
            drawDataHud(1.f + x, 20.f + y, localization::resources::hud::rsPunch, whatColor(player.inventory, 5, x, y));
            drawDataHud(
                1.f + x, 22.f + y, localization::resources::hud::rsKickShoes, whatColor(player.inventory, 6, x, y));
        }
    }
} // namespace game::systems
