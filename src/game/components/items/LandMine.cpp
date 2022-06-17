
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Land Mine
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

#include "logger/Logger.hpp"

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
        landMine.dropRate = 100;
        landMine.onApply = [](ecs::Entity player, ecs::SystemData data) {
            Player::placeLandMine(player, data);
            return true;
        };
        return landMine;
    }
} // namespace game::components
