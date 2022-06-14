/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#include "Item.hpp"
#include "logger/Logger.hpp"
#include "util/util.hpp"

namespace game::components
{
    std::vector<Item> Item::powerUps = {Item::SpeedShoes()};
    std::vector<Item> Item::powerDowns;
    std::vector<Item> Item::activables;

    bool Item::spawnRandomItem(ecs::SystemData data, raylib::core::Vector2u cell)
    {
        if (util::randInt(0, 99) >= 70)
            return false;
        return true;
    }
} // namespace game::components
