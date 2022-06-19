/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Smoke
*/

#ifndef GAME_SYSTEMS_SMOKE_HPP_
#define GAME_SYSTEMS_SMOKE_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Move smoke system
    struct MoveSmoke : public ecs::System {
        /// Move the smokes to follow their @a owners
        void run(ecs::SystemData data) override final;
    };

    /// Draw Smoke system
    struct DrawSmoke : public ecs::System {
        /// Draw the smokes
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_SMOKE_HPP_ */
