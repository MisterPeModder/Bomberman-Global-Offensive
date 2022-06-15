
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Bomb Down
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::BombDown()
    {
        Item bombDown;

        bombDown.type = Item::Type::PowerDown;
        bombDown.identifier = Item::Identifier::BombDown;
        bombDown.maxStack = 0;
        bombDown.name = "Bomb Down";
        bombDown.duration = std::chrono::milliseconds(0);
        bombDown.dropRate = 30;
        bombDown.onApply = [](ecs::Entity player, ecs::SystemData data) {
            auto &bombLimit = data.getStorage<Player>()[player.getId()].stats.bombLimit;

            if (bombLimit == 1)
                return false;
            bombLimit--;
            return true;
        };
        return bombDown;
    }
} // namespace game::components
