/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** SpeedShoes
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::SpeedShoes()
    {
        Item shoes;

        shoes.type = Item::Type::PowerUp;
        shoes.identifier = Item::Identifier::SpeedShoes;
        shoes.maxStack = 0;
        shoes.name = "Speed Shoes";
        shoes.duration = std::chrono::milliseconds::zero();
        shoes.dropRate = 30;
        shoes.onApply = [](ecs::Entity player, ecs::SystemData data) {
            auto &speed = data.getStorage<Player>()[player.getId()].stats.speed;

            if (speed < Player::Stats::DEFAULT_SPEED * 1.5f) {
                speed += Player::Stats::DEFAULT_SPEED * 0.1f;
                return true;
            }
            return false;
        };
        return shoes;
    }
} // namespace game::components
