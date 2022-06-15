/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Items
*/

#ifndef GAME_SYSTEMS_ITEMS_HPP_
#define GAME_SYSTEMS_ITEMS_HPP_

#include "Collision.hpp"
#include "ecs/Component.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/items/Item.hpp"
#include "game/components/items/ItemIdentifier.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game::systems
{
    struct PickupItem : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto &positions = data.getStorage<game::components::Position>();
            auto &sizes = data.getStorage<game::components::Size>();
            auto &entities = data.getResource<ecs::Entities>();
            raylib::shapes::Rectangle collideRect;

            for (auto [playerPos, playerSize, player, playerId] :
                ecs::join(positions, sizes, data.getStorage<game::components::Player>(), entities)) {
                for (auto [pos, size, itemId, id] :
                    ecs::join(positions, sizes, data.getStorage<game::components::ItemIdentifier>(), entities)) {
                    if (!Collision::getCollideRect(collideRect, playerPos, playerSize, pos, size))
                        continue;

                    player.pickupItem(playerId, itemId.identifier, data);
                    entities.kill(id);
                }
            }
        }
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_ITEMS_HPP_ */
