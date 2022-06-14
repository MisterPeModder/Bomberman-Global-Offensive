/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Rectangle
*/

#ifndef GAME_SYSTEMS_RECTANGLE_HPP_
#define GAME_SYSTEMS_RECTANGLE_HPP_

#include <iostream>
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Color.hpp"
#include "game/components/Rectangle.hpp"
#include "game/components/Position2D.hpp"
#include "game/components/Size2D.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game
{
    namespace systems
    {
        struct DrawRectangle : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [rectangle, pos, size, color] :
                    ecs::join(data.getStorage<game::components::Rectangle>(), data.getStorage<game::components::Position2D>(),
                        data.getStorage<game::components::Size2D>(), data.getStorage<game::components::Color>())) {
                    rectangle.draw(pos, size, color);
                }
            }
        };
    } // namespace systems
} // namespace game

#endif
