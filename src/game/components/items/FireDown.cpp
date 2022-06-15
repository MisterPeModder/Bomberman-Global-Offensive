
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
        Item fireUp;

        fireUp.type = Item::Type::PowerUp;
        fireUp.identifier = Item::Identifier::FireDown;
        fireUp.maxStack = 0;
        fireUp.name = "Fire Down";
        fireUp.duration = std::chrono::milliseconds(0);
        fireUp.dropRate = 30;
        fireUp.onApply = [](ecs::Entity player, ecs::SystemData data) {
            auto &bombRange = data.getStorage<Player>()[player.getId()].stats.bombRange;

            if (bombRange == 1)
                return false;
            bombRange--;
            return true;
        };
        return fireUp;
    }
} // namespace game::components
