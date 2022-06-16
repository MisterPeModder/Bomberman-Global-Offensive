
/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Inverted controls
*/

#include "Item.hpp"
#include "game/components/Player.hpp"
#include "game/components/Velocity.hpp"

namespace game::components
{
    Item Item::InvertedControls()
    {
        Item invertedControls;

        invertedControls.type = Item::Type::PowerDown;
        invertedControls.identifier = Item::Identifier::InvertedControls;
        invertedControls.maxStack = 0;
        invertedControls.name = "Inverted Controls";
        invertedControls.duration = std::chrono::milliseconds(4000);
        invertedControls.dropRate = 10;
        invertedControls.onApply = [](ecs::Entity player, ecs::SystemData data) {
            data.getStorage<Player>()[player.getId()].stats.inverted = true;
            data.getStorage<Velocity>()[player.getId()] *= {-1.f, 0.f, -1.f};
            return true;
        };
        invertedControls.onTimedOut = [](ecs::Entity player, ecs::SystemData data) {
            data.getStorage<Player>()[player.getId()].stats.inverted = false;
            data.getStorage<Velocity>()[player.getId()] *= {-1.f, 0.f, -1.f};
        };
        return invertedControls;
    }
} // namespace game::components
