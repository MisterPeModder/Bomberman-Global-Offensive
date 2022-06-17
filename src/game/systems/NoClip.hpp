/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** NoClip
*/

#ifndef GAME_COMPONENTS_NOCLIP_HPP_
#define GAME_COMPONENTS_NOCLIP_HPP_

#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "game/components/BombNoClip.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"

namespace game::systems
{
    /// Disables the bomb no clip when the player walk off of the bomb position.
    struct DisableBombNoClip : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [position, size, bombNoClip] : ecs::join(data.getStorage<game::components::Position>(),
                     data.getStorage<game::components::Size>(), data.getStorage<game::components::BombNoClip>())) {
                if (bombNoClip.enabled && !bombNoClip.matchEntityPosition(position, size))
                    bombNoClip.enabled = false;
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_COMPONENTS_NOCLIP_HPP_ */
