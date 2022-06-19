/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Collision
*/

#include "Collision.hpp"
#include <cmath>
#include "ecs/join.hpp"
#include "game/components/Bomb.hpp"
#include "game/components/BombNoClip.hpp"
#include "game/components/Collidable.hpp"
#include "game/components/Destructible.hpp"
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
        auto maybeDestructible = ecs::maybe(data.getStorage<Destructible>());
        raylib::shapes::Rectangle collideRect;

        for (auto [pos1, size1, vel1, id1, c1, bombNoClip, player1, bomb1] :
            ecs::join(positions, sizes, velocities, entities, collidable, maybeBombNoClip, maybePlayer, maybeBomb)) {
            for (auto [pos2, size2, vel2, id2, c2, player2, bomb2, destructible] : ecs::join(positions, sizes,
                     optionalVelocity, entities, collidable, maybePlayer, maybeBomb, maybeDestructible)) {
                (void)c1;
                (void)c2;
                /// Do not collide entities with themselves
                if (id1.getId() == id2.getId())
                    continue;
                /// If entity1 has a bomb no clip enabled and entity 2 is the ignored (static) bomb we ignore the
                /// collision.
                if (bombNoClip && bombNoClip->enabled && bomb2 && !vel2 && bombNoClip->matchEntityPosition(pos2, size2))
                    continue;
                if (!getCollideRect(collideRect, pos1, size1, pos2, size2))
                    continue;

                /// Bomb related tests
                if (bomb1 || bomb2) {
                    /// Landmines explode on first collision
                    if (bomb2 && bomb2->type == Bomb::Type::LandMine) {
                        bomb2->explode(pos2, data, id2);
                        break;
                    }
                    /// Kicked bomb(s)
                    if (bomb1 || (bomb2 && vel2)) {
                        if (bomb1)
                            bomb1->explode(pos1, data, id1);
                        if (bomb2)
                            bomb2->explode(pos2, data, id2);
                        break;
                        // /// Two kicked bombs -> Explode
                        // if (bomb1 && bomb2 && vel2) {
                        //     bomb1->explode(pos1, data, id1);
                        //     break;
                        // }
                        // /// Only one kicked bomb
                        // else {
                        //     if (bomb1 && bomb2) {
                        //         if (fabsf(vel1.x) > fabsf(vel1.z))
                        //             pos1.x -= std::copysignf(1.f, vel1.x);
                        //         else
                        //             pos1.z -= std::copysignf(1.f, vel1.z);
                        //     }
                        //     if (bomb1)
                        //         bomb1->stop(data, id1);
                        //     else
                        //         bomb2->stop(data, id2);
                        //     if (player1 || player2)
                        //         Logger::logger.log(Logger::Severity::Debug, "Player stun");
                        //     break;
                        // }

                    }
                    /// Static bomb (can't be bomb1 because first entity must have a velocity)
                    else if (player1 && player1->inventory[Item::Identifier::KickShoes]) {
                        raylib::core::Vector3f posDelta = pos2 - pos1;
                        /// Kick bomb if the player is moving toward it.
                        if ((std::fabs(posDelta.x) > std::fabs(posDelta.z)) ? (posDelta.x * vel1.x > 0)
                                                                            : (posDelta.z * vel1.z > 0))
                            bomb2->setVelocity(data, id2, {vel1.x * 1.3f, 0.f, vel1.z * 1.3f});
                    }
                }

                if (player1 && player1->stats.clipState != Player::Stats::ClipState::Default && !vel2 && !bomb2
                    && destructible)
                    continue;

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
