
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** No clip
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::NoClip()
    {
        Item noClip;

        noClip.type = Item::Type::Activable;
        noClip.identifier = Item::Identifier::NoClip;
        noClip.maxStack = 1;
        noClip.name = "Wall Pass";
        noClip.duration = std::chrono::milliseconds(3000);
        noClip.dropRate = 50;
        noClip.onApply = [](ecs::Entity player, ecs::SystemData data) {
            // Player::placeLandMine(player, data);
            return true;
        };
        noClip.onTimedOut = [](ecs::Entity placer, ecs::SystemData data) {};
        return noClip;
    }
} // namespace game::components
