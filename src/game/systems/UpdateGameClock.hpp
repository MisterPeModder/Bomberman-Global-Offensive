/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** UpdateGameClock
*/

#ifndef GAME_SYSTEMS_UPDATEGAMECLOCK_HPP_
#define GAME_SYSTEMS_UPDATEGAMECLOCK_HPP_

#include "ecs/System.hpp"
#include "game/resources/GameClock.hpp"

namespace game::systems
{
    /// Update the game clock internal time.
    struct UpdateGameClock : public ecs::System {
        void run(ecs::SystemData data) override final { data.getResource<game::resources::GameClock>().update(); }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_UPDATEGAMECLOCK_HPP_ */
