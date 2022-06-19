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
        void run(ecs::SystemData data) override final;

      private:
        raylib::core::Color DrawHud::whatColor(ecs::SystemData data, int id);
        void drawDataHud(float x, float y, std::string text, raylib::core::Color color);
    };
} // namespace game::systems
#endif /*!DRAW_HUD_HPP_*/