/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Item
*/

#include "Item.hpp"

namespace game::components
{
    std::vector<Item> Item::powerUps = {Item::SpeedShoes()};
    std::vector<Item> Item::powerDowns;
    std::vector<Item> Item::activables;
} // namespace game::components
