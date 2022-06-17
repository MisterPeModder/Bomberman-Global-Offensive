
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Fire Up
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::FireUp()
    {
        Item fireUp;

        fireUp.type = Item::Type::PowerUp;
        fireUp.identifier = Item::Identifier::FireUp;
        fireUp.maxStack = 0;
        fireUp.name = "Fire Up";
        fireUp.duration = std::chrono::milliseconds::zero();
        fireUp.dropRate = 30;
        fireUp.onApply = [](ecs::Entity player, ecs::SystemData data) {
            data.getStorage<Player>()[player.getId()].stats.bombRange++;
            return true;
        };
        return fireUp;
    }
} // namespace game::components
