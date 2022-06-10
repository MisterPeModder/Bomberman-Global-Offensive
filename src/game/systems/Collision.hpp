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

namespace game::systems
{
    /// Collisions resolver system
    struct Collision : public ecs::System {
        /// Resolves the collisions of dynamics collidable entities.
        void run(ecs::SystemData data) override final;

      private:
        /// Apply the collision resolution on a specific position.
        void resolveCollision(const ::Rectangle collideRectangle, float scale, game::components::Position &pos) const;
    };
} // namespace game::systems

#endif /* !GAME_SYSTEMS_COLLISION_HPP_ */
