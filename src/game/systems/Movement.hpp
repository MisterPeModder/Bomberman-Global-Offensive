/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movement
*/

#ifndef GAME_SYSTEMS_MOVEMENT_HPP_
#define GAME_SYSTEMS_MOVEMENT_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Movement system
    struct Movement : public ecs::System {
        /// Apply all the velocities on the positions.
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_MOVEMENT_HPP_ */
