
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
        bombUp.duration = std::chrono::milliseconds(0);
        bombUp.dropRate = 30;
        bombUp.onApply = [](ecs::Entity player, ecs::SystemData data) {
            data.getStorage<Player>()[player.getId()].stats.bombLimit++;
        };
        return bombUp;
    }
} // namespace game::components
