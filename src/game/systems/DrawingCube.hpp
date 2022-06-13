/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** DrawingCube
*/

#ifndef GAME_SYSTEMS_DRAWINGCUBE_HPP_
#define GAME_SYSTEMS_DRAWINGCUBE_HPP_

#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Cube.hpp"

#include "game/components/Destructible.hpp"
#include "game/components/Living.hpp"

namespace game::systems
{
    /// Drawing cube system
    struct DrawingCube : public ecs::System {
        /// Draws all the cubes.
        void run(ecs::SystemData data) override final
        {
            auto maybeDestructible = ecs::maybe(data.getStorage<game::components::Destructible>());
            auto maybeLiving = ecs::maybe(data.getStorage<game::components::Living>());

            for (auto [cube, destructible, living] :
                ecs::join(data.getStorage<game::components::Cube>(), maybeDestructible, maybeLiving)) {
                if ((destructible && destructible->destroyed) || (living && living->hp == 0))
                    continue;
                cube.cube.draw();
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_DRAWINGCUBE_HPP_ */
