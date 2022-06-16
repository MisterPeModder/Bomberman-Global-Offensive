
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Stun Grenade
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::StunGrenade()
    {
        Item stunGrenade;

        stunGrenade.type = Item::Type::Activable;
        stunGrenade.identifier = Item::Identifier::StunGrenade;
        stunGrenade.maxStack = 0;
        stunGrenade.name = "Stun Grenade";
        stunGrenade.duration = std::chrono::milliseconds(4000);
        stunGrenade.dropRate = 50;
        stunGrenade.onApply = [](ecs::Entity player, ecs::SystemData data) { return true; };
        stunGrenade.onTimedOut = [](ecs::Entity player, ecs::SystemData data) {};
        return stunGrenade;
    }
} // namespace game::components
