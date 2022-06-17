
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Stun Grenade
*/

#include "Item.hpp"
#include "ecs/join.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::SmokeGrenade()
    {
        Item smokeGrenade;

        smokeGrenade.type = Item::Type::Activable;
        smokeGrenade.identifier = Item::Identifier::SmokeGrenade;
        smokeGrenade.maxStack = 0;
        smokeGrenade.name = "Smoke Grenade";
        smokeGrenade.duration = std::chrono::milliseconds(7000);
        smokeGrenade.dropRate = 65;
        smokeGrenade.onApply = [](ecs::Entity placer, ecs::SystemData data) { return true; };
        smokeGrenade.onTimedOut = [](ecs::Entity placer, ecs::SystemData data) {};
        return smokeGrenade;
    }
} // namespace game::components
