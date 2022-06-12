/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb
*/

#ifndef GAME_SYSTEMS_BOMB_HPP_
#define GAME_SYSTEMS_BOMB_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    /// Draw bomb system
    struct DrawBomb : public ecs::System {
        /// Draw the bombs
        void run(ecs::SystemData data) override final;
    };

    /// Explode bomb system
    struct ExplodeBomb : public ecs::System {
        /// Explode the bombs if needed
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_BOMB_HPP_ */
