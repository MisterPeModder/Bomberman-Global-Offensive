/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collision
*/

#include "Collision.hpp"
#include "ecs/join.hpp"
#include "game/components/Bomb.hpp"
#include "game/components/BombNoClip.hpp"
#include "game/components/Collidable.hpp"
#include "game/components/Player.hpp"
#include "game/components/Size.hpp"
#include "game/components/Velocity.hpp"

#include "logger/Logger.hpp"

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
        auto maybeBombNoClip = ecs::maybe(data.getStorage<BombNoClip>());
        auto maybeBomb = ecs::maybe(data.getStorage<Bomb>());
        auto optionalVelocity = ecs::maybe(velocities);
        auto maybePlayer = ecs::maybe(data.getStorage<Player>());
        raylib::shapes::Rectangle collideRect;

        for (auto [pos1, size1, vel1, id1, c1, bombNoClip, player] :
            ecs::join(positions, sizes, velocities, entities, collidable, maybeBombNoClip, maybePlayer)) {
            for (auto [pos2, size2, vel2, id2, c2, bomb] :
                ecs::join(positions, sizes, optionalVelocity, entities, collidable, maybeBomb)) {
                (void)c1;
                (void)c2;
                /// Do not collide entities with themselves
                if (id1.getId() == id2.getId())
                    continue;
                /// If entity1 has a bomb no clip enabled and entity 2 is the ignored (static) bomb we ignore the
                /// collision.
                if (bombNoClip && bombNoClip->enabled && bomb && !vel2 && bombNoClip->matchEntityPosition(pos2))
                    continue;
                if (!getCollideRect(collideRect, pos1, size1, pos2, size2))
                    continue;

                /// Kick(ed) bomb related tests
                if (player && bomb) {
                    if (!vel2 && player->inventory[Item::Identifier::KickShoes]) {
                        raylib::core::Vector3f posDelta = pos2 - pos1;
                        /// Kick bomb if the player is moving toward it.
                        if ((abs(posDelta.x) > abs(posDelta.x)) ? (posDelta.x * vel1.x > 0)
                                                                : (posDelta.z * vel1.z > 0)) {
                            bomb->kick(data, id2, vel1);
                            break;
                        }
                    }
                }

                float firstMovePercent = (vel2) ? 0.5f : 1.f;
                resolveCollision(collideRect.getRaylibRectangle(), firstMovePercent, pos1);
                resolveCollision(collideRect.getRaylibRectangle(), (1 - firstMovePercent), pos2);
            }
        }
    }

    bool Collision::getCollideRect(raylib::shapes::Rectangle &collideRect, raylib::core::Vector3f pos1,
        raylib::core::Vector3f size1, raylib::core::Vector3f pos2, raylib::core::Vector3f size2)
    {
        /// Do not make further check because entities are too far to collide
        if (abs(pos1.x - pos2.x) * 2 > (size1.x + size2.x) && abs(pos1.z - pos2.z) * 2 > (size1.z + size2.z))
            return false;

        raylib::shapes::Rectangle rect1(raylib::core::Vector2(pos1.x - size1.x / 2.f, pos1.z - size1.z / 2.f),
            raylib::core::Vector2(size1.x, size1.z));
        raylib::shapes::Rectangle rect2(raylib::core::Vector2(pos2.x - size2.x / 2.f, pos2.z - size2.z / 2.f),
            raylib::core::Vector2(size2.x, size2.z));

        if (!rect1.checkCollision(rect2))
            return false;
        collideRect = rect1.getCollision(rect2);
        return true;
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
