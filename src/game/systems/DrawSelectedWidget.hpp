/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** DrawSelectedWidget
*/

#ifndef GAME_SYSTEMS_DRAWSELECTEDWIDGET_HPP_
#define GAME_SYSTEMS_DRAWSELECTEDWIDGET_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"
#include "game/gui/components/Widget.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game::systems
{
    /// Draw selected widget system
    struct DrawSelectedWidget : public ecs::System {
        /// Draw the selected widget
        void run(ecs::SystemData data) override final
        {
            for (auto [widget, pos] :
                ecs::join(data.getStorage<game::gui::Widget>(), data.getStorage<game::components::Position>())) {
                if (widget.selected) {
                    raylib::shapes::Rectangle::draw({(pos.x - 2) / 100 * raylib::core::Window::getWidth(),
                                                        (pos.y - 2) / 100 * raylib::core::Window::getHeight()},
                        {10, 10}, raylib::core::Color::YELLOW);
                    raylib::shapes::Rectangle::draw({(pos.x - 2) / 100 * raylib::core::Window::getWidth(),
                                                        (pos.y - 2) / 100 * raylib::core::Window::getHeight()},
                        {8, 8}, raylib::core::Color::BLACK);
                }
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_DRAWSELECTEDWIDGET_HPP_ */
