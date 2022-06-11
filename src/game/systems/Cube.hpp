#ifndef GAME_SYSTEMS_CUBE_HPP_
#define GAME_SYSTEMS_CUBE_HPP_

#include <iostream>
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Color.hpp"
#include "game/components/Model.hpp"
#include "game/components/Position.hpp"
#include "game/components/Scale.hpp"
#include "game/components/Size.hpp"
#include "game/components/Cube.hpp"
#include "raylib/shapes/Cube.hpp"

namespace game
{
    namespace systems
    {
        struct DrawCube : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                for (auto [cube, pos, scale, color] :
                    ecs::join(data.getStorage<game::components::Cube>(), data.getStorage<game::components::Position>(),
                        data.getStorage<game::components::Scale>(), data.getStorage<game::components::Color>())) {
                    cube.draw(pos, scale.scale, color);
                }
            }
        };
    } // namespace systems
} // namespace game

#endif
