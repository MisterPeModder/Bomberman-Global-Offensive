/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** DrawSelectedWidget
*/

#ifndef GAME_SYSTEMS_DRAWSELECTEDWIDGET_HPP_
#define GAME_SYSTEMS_DRAWSELECTEDWIDGET_HPP_

#include "ecs/join.hpp"
#include "ecs/System.hpp"
#include "ecs/Storage.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"
#include "game/gui/components/Widget.hpp"
#include "raylib/shapes/Rectangle.hpp"
#include "raylib/core/Color.hpp"

namespace game::systems
{
    /// Drawing cube system
    struct DrawSelectedWidget : public ecs::System {
        /// Draws all the cubes.
        void run(ecs::SystemData data) override final
        {
            for (auto [widget, pos] : ecs::join(data.getStorage<game::gui::Widget>(),
                     data.getStorage<game::components::Position>())) {
                if (widget.selected) {
                    raylib::shapes::Rectangle::draw({pos.x - 15, pos.y - 15}, {10, 10}, raylib::core::Color::YELLOW);
                    raylib::shapes::Rectangle::draw({pos.x - 15, pos.y - 15}, {8, 8}, raylib::core::Color::BLACK);
                }
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_DRAWSELECTEDWIDGET_HPP_ */
