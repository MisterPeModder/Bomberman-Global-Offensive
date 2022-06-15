/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Items
*/

#include "Items.hpp"
#include "Collision.hpp"
#include "ecs/Component.hpp"
#include "ecs/join.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/Size.hpp"
#include "game/components/items/Item.hpp"
#include "game/components/items/ItemIdentifier.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game::systems
{
    void PickupItem::run(ecs::SystemData data)
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
} // namespace game::systems