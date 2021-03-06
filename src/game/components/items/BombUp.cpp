
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb Up
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::BombUp()
    {
        Item bombUp;

        bombUp.type = Item::Type::PowerUp;
        bombUp.identifier = Item::Identifier::BombUp;
        bombUp.maxStack = 0;
        bombUp.name = "Bomb Up";
        bombUp.duration = std::chrono::milliseconds::zero();
        bombUp.dropRate = 30;
        bombUp.onApply = [](ecs::Entity player, ecs::SystemData data) {
            auto &limit = data.getStorage<Player>()[player.getId()].stats.bombLimit;

            if (limit < 9)
                limit++;
            return true;
        };
        return bombUp;
    }
} // namespace game::components
