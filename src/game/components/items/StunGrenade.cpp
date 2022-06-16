
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Stun Grenade
*/

#include "Item.hpp"
#include "ecs/join.hpp"
#include "game/components/Player.hpp"
#include "game/components/Velocity.hpp"

namespace game::components
{
    Item Item::StunGrenade()
    {
        Item stunGrenade;

        stunGrenade.type = Item::Type::Activable;
        stunGrenade.identifier = Item::Identifier::StunGrenade;
        stunGrenade.maxStack = 0;
        stunGrenade.name = "Stun Grenade";
        stunGrenade.duration = std::chrono::milliseconds(4000);
        stunGrenade.dropRate = 50;
        stunGrenade.onApply = [](ecs::Entity placer, ecs::SystemData data) {
            auto &players = data.getStorage<Player>();

            /// Test if a stun grenade isn't already in effect.
            for (auto [player] : ecs::join(players))
                /// If it is, the grenade won't be consumed.
                if (player.stats.slowness)
                    return false;

            /// Apply the slowness effect on all ennnemies.
            for (auto [player, velocity, playerId] :
                ecs::join(players, data.getStorage<Velocity>(), data.getResource<ecs::Entities>())) {
                if (playerId.getId() == placer.getId())
                    continue;
                player.stats.slowness = true;
                velocity *= {0.25f, 0.f, 0.25f};
            }
            return true;
        };
        stunGrenade.onTimedOut = [](ecs::Entity placer, ecs::SystemData data) {
            for (auto [player, velocity] : ecs::join(data.getStorage<Player>(), data.getStorage<Velocity>())) {
                if (!player.stats.slowness)
                    continue;
                player.stats.slowness = false;
                velocity *= {4.f, 0.f, 4.f};
            }
        };
        return stunGrenade;
    }
} // namespace game::components
