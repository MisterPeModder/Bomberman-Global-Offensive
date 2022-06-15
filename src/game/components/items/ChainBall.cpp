/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** ChainBall
*/

#include "Item.hpp"
#include "game/components/Player.hpp"

namespace game::components
{
    Item Item::ChainBall()
    {
        Item chainBall;

        chainBall.type = Item::Type::PowerDown;
        chainBall.identifier = Item::Identifier::ChainBall;
        chainBall.maxStack = 5;
        chainBall.name = "Chain ball";
        chainBall.duration = std::chrono::milliseconds(0);
        chainBall.dropRate = 30;
        chainBall.onApply = [](ecs::Entity player, ecs::SystemData data) {
            data.getStorage<Player>()[player.getId()].stats.speed -= Player::Stats::DEFAULT_SPEED * 0.1f;
            return true;
        };
        return chainBall;
    }
} // namespace game::components
