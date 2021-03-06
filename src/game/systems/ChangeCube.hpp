/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** ChangeCube
*/

#ifndef GAME_SYSTEMS_CHANGECUBE_HPP_
#define GAME_SYSTEMS_CHANGECUBE_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Cube.hpp"
#include "game/components/CubeColor.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"

namespace game::systems
{
    /// ChangeCube system
    struct ChangeCube : public ecs::System {
        /// Apply changes on the cubes.
        void run(ecs::SystemData data) override final
        {
            for (auto [cube, pos, col, size] :
                ecs::join(data.getStorage<game::components::Cube>(), data.getStorage<game::components::Position>(),
                    data.getStorage<game::components::CubeColor>(), data.getStorage<game::components::Size>())) {
                cube.setPosition(pos);
                cube.setColor(col);
                cube.setSize(size);
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_CHANGECUBE_HPP_ */
