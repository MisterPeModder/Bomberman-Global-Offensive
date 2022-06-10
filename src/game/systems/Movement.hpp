/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Movement
*/

#ifndef GAME_SYSTEMS_MOVEMENT_HPP_
#define GAME_SYSTEMS_MOVEMENT_HPP_

#include "ecs/System.hpp"

namespace game
{
    struct Movement : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game

#endif /* !GAME_SYSTEMS_MOVEMENT_HPP_ */
