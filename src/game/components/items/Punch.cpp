
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Punch
*/

#include "Item.hpp"
#include "game/components/Player.hpp"
#include "game/components/Velocity.hpp"

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
            data.getStorage<Player>()[placer.getId()].stun(placer, data, std::chrono::milliseconds(2000));
            return true;
        };
        return punch;
    }
} // namespace game::components
