/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collision
*/

#ifndef GAME_SYSTEMS_COLLISION_HPP_
#define GAME_SYSTEMS_COLLISION_HPP_

#include "ecs/System.hpp"
#include "game/components/Position.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game
{
    struct Collision : public ecs::System {
        void run(ecs::SystemData data) override final;

      private:
        void resolveCollision(const ::Rectangle collideRectangle, float scale, Position &pos) const;
    };
} // namespace game

#endif /* !GAME_SYSTEMS_COLLISION_HPP_ */
