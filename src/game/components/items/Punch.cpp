
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Punch
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

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
        punch.onApply = [](ecs::Entity player, ecs::SystemData data) { return true; };
        return punch;
    }
} // namespace game::components
