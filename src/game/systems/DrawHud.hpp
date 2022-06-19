/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** DrawHud
*/

#ifndef DRAW_HUD_HPP_
#define DRAW_HUD_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Hud.hpp"
#include "game/components/Position.hpp"
#include "game/components/Textual.hpp"

namespace game::systems
{
    /// Draw text system.
    struct DrawHud : public ecs::System {
        /// Draw all the entities with the components Player.
        ///
        /// @param data view on the world.
        enum hudPosition {
            x1 = 0,
            y1 = 0,
            x2 = 0,
            y2 = 700,
            x3 = 1800,
            y3 = 0,
            x4 = 1800,
            y4 = 700,

        };
        void run(ecs::SystemData data) override final;

      private:
        void drawDataHud(int x, int y, std::string text, raylib::core::Color color);
    };
} // namespace game::systems
#endif /*!DRAW_HUD_HPP_*/