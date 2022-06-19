
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Punch
*/

#include <cmath>
#include "Item.hpp"
#include "ecs/join.hpp"
#include "game/Game.hpp"
#include "game/components/Player.hpp"
#include "game/components/Position.hpp"
#include "game/components/Velocity.hpp"
#include "raylib/core/Vector2.hpp"

namespace game::components
{
    Item Item::Punch()
    {
        Item punch;

        punch.type = Item::Type::Activable;
        punch.identifier = Item::Identifier::Punch;
        punch.maxStack = 0;
        punch.name = "Punch";
        punch.duration = std::chrono::milliseconds::zero();
        punch.dropRate = 20;
        punch.onApply = [](ecs::Entity placer, ecs::SystemData data) {
            auto &positions = data.getStorage<Position>();
            auto &placerPos = positions[placer.getId()];

            /// Punch all nearby ennemies
            for (auto [pos, player, entity] :
                ecs::join(positions, data.getStorage<Player>(), data.getResource<ecs::Entities>())) {
                if (entity.getId() == placer.getId())
                    continue;

                if (std::fabs(pos.x - placerPos.x) + std::fabs(pos.z - placerPos.z) <= 3.f)
                    player.stun(entity, data, std::chrono::milliseconds(2000));
            }
            return true;
        };
        return punch;
    }
} // namespace game::components
