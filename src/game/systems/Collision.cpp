/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collision
*/

#include "Collision.hpp"
#include "ecs/join.hpp"
#include "game/components/Collidable.hpp"
#include "game/components/Destructible.hpp"
#include "game/components/Size.hpp"
#include "game/components/Velocity.hpp"

using namespace game::components;

namespace game::systems
{
    void Collision::run(ecs::SystemData data)
    {
        auto &positions = data.getStorage<Position>();
        auto &sizes = data.getStorage<Size>();
        auto &entities = data.getResource<ecs::Entities>();
        auto &collidable = data.getStorage<Collidable>();
        auto &velocities = data.getStorage<Velocity>();
        auto optionnalVelocity = ecs::maybe(velocities);
        auto maybeDestructible = ecs::maybe(data.getStorage<Destructible>());

        for (auto [pos1, size1, vel1, id1, c1] : ecs::join(positions, sizes, velocities, entities, collidable)) {
            for (auto [pos2, size2, vel2, id2, c2, destructible] :
                ecs::join(positions, sizes, optionnalVelocity, entities, collidable, maybeDestructible)) {
                (void)c1;
                (void)c2;
                /// Do not collide entities with themselves
                if (id1.getId() == id2.getId() || (destructible && destructible->destructed))
                    continue;
                /// Do not make further check because entities are too far to collide
                if (abs(pos1.x - pos2.x) * 2 > (size1.x + size2.x) && abs(pos1.z - pos2.z) * 2 > (size1.z + size2.z))
                    continue;

                raylib::shapes::Rectangle rect1(raylib::core::Vector2(pos1.x - size1.x / 2.f, pos1.z - size1.z / 2.f),
                    raylib::core::Vector2(size1.x, size1.z));
                raylib::shapes::Rectangle rect2(raylib::core::Vector2(pos2.x - size2.x / 2.f, pos2.z - size2.z / 2.f),
                    raylib::core::Vector2(size2.x, size2.z));

                if (!rect1.checkCollision(rect2))
                    continue;
                ::Rectangle collideRect = rect1.getCollision(rect2).getRaylibRectangle();

                float firstMovePercent = (vel2) ? 0.5f : 1.f;
                resolveCollision(collideRect, firstMovePercent, pos1);
                resolveCollision(collideRect, (1 - firstMovePercent), pos2);
            }
        }
    }

    void Collision::resolveCollision(const ::Rectangle collideRectangle, float scale, Position &pos) const
    {
        if (scale <= 0.f)
            return;
        if (collideRectangle.height < collideRectangle.width)
            pos.x += collideRectangle.height * scale * ((collideRectangle.x < pos.x) ? 1 : -1);
        else
            pos.z += collideRectangle.width * scale * ((collideRectangle.y < pos.z) ? 1 : -1);
    }

} // namespace game::systems
