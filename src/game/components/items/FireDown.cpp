
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Fire Down
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::FireDown()
    {
        Item fireDown;

        fireDown.type = Item::Type::PowerDown;
        fireDown.identifier = Item::Identifier::FireDown;
        fireDown.maxStack = 0;
        fireDown.name = "Fire Down";
        fireDown.duration = std::chrono::milliseconds::zero();
        fireDown.dropRate = 30;
        fireDown.onApply = [](ecs::Entity player, ecs::SystemData data) {
            auto &bombRange = data.getStorage<Player>()[player.getId()].stats.bombRange;

            if (bombRange == 1)
                return false;
            bombRange--;
            return true;
        };
        return fireDown;
    }
} // namespace game::components
