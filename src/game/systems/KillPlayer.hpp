/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Cube
*/

#ifndef GAME_SYSTEMS_LIVING_HPP_
#define GAME_SYSTEMS_LIVING_HPP_

#include <iostream>
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/Player.hpp"
#include "game/components/Living.hpp"
#include "raylib/model/Animation.hpp"

namespace game
{
    namespace systems
    {
        struct KillPlayer : public ecs::System {
            void run(ecs::SystemData data) override final
            {
                // for (auto [player, living, entity] : ecs::join(data.getStorage<game::components::Player>(), data.getStorage<game::components::Living>(), data.getResource<ecs::Entities>())) {
                //     if (player.animation == game::components::Player::Animations::Die)
                //         data.getResource<ecs::Entities>().kill(entity.getId());
                // }
            }
        };
    } // namespace systems
} // namespace game

#endif
