
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Kick Shoes
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::KickShoes()
    {
        Item kickShoes;

        kickShoes.type = Item::Type::PowerUp;
        kickShoes.identifier = Item::Identifier::KickShoes;
        kickShoes.maxStack = 1;
        kickShoes.name = "Kick Shoes";
        kickShoes.duration = std::chrono::milliseconds(0);
        kickShoes.dropRate = 10;
        /// Item is a passive, applied on collision with bombs
        kickShoes.onApply = [](ecs::Entity player, ecs::SystemData data) {
            (void)player;
            (void)data;
        };
        return kickShoes;
    }
} // namespace game::components
