/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** NoClip
*/

#ifndef GAME_COMPONENTS_NOCLIP_HPP_
#define GAME_COMPONENTS_NOCLIP_HPP_

#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "ecs/storage.hpp"
#include "game/components/BombNoClip.hpp"
#include "game/components/Position.hpp"

namespace game::systems
{
    struct RemovesBombNoClip : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [position, bombNoClip] : ecs::join(
                     data.getStorage<game::components::Position>(), data.getStorage<game::components::BombNoClip>())) {
                if (bombNoClip.enabled && !bombNoClip.matchEntityPosition(position))
                    bombNoClip.enabled = false;
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_COMPONENTS_NOCLIP_HPP_ */
