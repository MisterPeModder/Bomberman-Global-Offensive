
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Land Mine
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::LandMine()
    {
        Item landMine;

        landMine.type = Item::Type::Activable;
        landMine.identifier = Item::Identifier::LandMine;
        landMine.maxStack = 0;
        landMine.name = "Land Mine";
        landMine.duration = std::chrono::milliseconds::zero();
        landMine.dropRate = 20;
        landMine.onApply = [](ecs::Entity player, ecs::SystemData data) {
            Player::placeBomb(player, data, Bomb::Type::LandMine);
            return true;
        };
        return landMine;
    }
} // namespace game::components
