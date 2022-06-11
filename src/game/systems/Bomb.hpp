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
    struct DrawBomb : public ecs::System {
        void run(ecs::SystemData data) override final;
    };

    struct ExplodeBomb : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_BOMB_HPP_ */
