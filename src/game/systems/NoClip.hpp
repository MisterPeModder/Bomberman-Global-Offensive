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
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"
#include "game/resources/Map.hpp"

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

    /// Disables the no clip when the player walk off of a crate position
    struct DisableNoClip : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto &map = data.getResource<game::resources::Map>();

            for (auto [player, position] :
                ecs::join(data.getStorage<game::components::Player>(), data.getStorage<game::components::Position>())) {
                if (player.stats.clipState == game::components::Player::Stats::ClipState::WaitNoCollision
                    && map.map.getElement(Game::worldPosToMapCell(position)) == map::Map::Element::Empty)
                    player.stats.clipState = game::components::Player::Stats::ClipState::Default;
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_COMPONENTS_NOCLIP_HPP_ */
