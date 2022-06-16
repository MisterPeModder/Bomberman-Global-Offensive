/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Items
*/

#ifndef GAME_SYSTEMS_ITEMS_HPP_
#define GAME_SYSTEMS_ITEMS_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    struct PickupItem : public ecs::System {
        void run(ecs::SystemData data) override final;
    };

    struct UpdateItemTimer : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_ITEMS_HPP_ */
