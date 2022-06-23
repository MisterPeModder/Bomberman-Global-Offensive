/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** UpdateHud
*/

#ifndef GAME_SYSTEMS_UPDATEHUD_HPP_
#define GAME_SYSTEMS_UPDATEHUD_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    struct UpdateHud : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_UPDATEHUD_HPP_ */
