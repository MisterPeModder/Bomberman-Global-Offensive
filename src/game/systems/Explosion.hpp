/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Cube
*/

#ifndef GAME_SYSTEMS_EXPLOSIONS_HPP_
#define GAME_SYSTEMS_EXPLOSIONS_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Fade down the explosions and kill them.
    struct ClearExplosions : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif
