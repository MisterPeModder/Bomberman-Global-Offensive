/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Temp
*/

#ifndef TEMP_HPP_
#define TEMP_HPP_

#include "Collidable.hpp"
#include "Position.hpp"
#include "Size.hpp"
#include "Velocity.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"
#include "logger/Logger.hpp"
#include "raylib/core/Color.hpp"
#include "raylib/shapes/Cube.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game
{
    struct CubeColor : public ecs::Component, public raylib::core::Color {
        CubeColor(unsigned char cr, unsigned char cg, unsigned char cb, unsigned char ca)
            : raylib::core::Color(cr, cg, cb, ca)
        {
        }
        CubeColor(const raylib::core::Color &other) : raylib::core::Color(other) {}
    };

    struct Cube : public ecs::Component {
        raylib::shapes::Cube cube;

        Cube() : cube() {}
        Cube(raylib::core::Vector3 position, raylib::core::Vector3 size, Color color) : cube(position, size, color) {}
    };

    struct ChangeCube : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [cube, pos, col, size] : ecs::join(data.getStorage<Cube>(), data.getStorage<Position>(),
                     data.getStorage<CubeColor>(), data.getStorage<Size>())) {
                cube.cube.setPosition(pos);
                cube.cube.setColor(col);
                cube.cube.setSize(size);
            }
        }
    };

    struct DrawingCube : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            for (auto [cube] : ecs::join(data.getStorage<Cube>())) {
                cube.cube.draw();
            }
        }
    };

    struct Movement : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            float seconds = data.getResource<ecs::Timer>().elapsed();

            for (auto [pos, vel] : ecs::join(data.getStorage<Position>(), data.getStorage<Velocity>())) {
                // no friction here, just plain old perpertual motion
                pos.x += vel.x * seconds;
                pos.y += vel.y * seconds;
                pos.z += vel.z * seconds;
            }
        }
    };

    struct Collisions : public ecs::System {
        void run(ecs::SystemData data) override final
        {
            auto optionnalVelocity = ecs::maybe(data.getStorage<Velocity>());
            auto &positions = data.getStorage<Position>();
            auto &sizes = data.getStorage<Size>();
            auto &entities = data.getResource<ecs::Entities>();
            auto &collidable = data.getStorage<Collidable>();

            for (auto [pos1, size1, vel1, id1, c1] :
                ecs::join(positions, sizes, optionnalVelocity, entities, collidable)) {
                for (auto [pos2, size2, vel2, id2, c2] :
                    ecs::join(positions, sizes, optionnalVelocity, entities, collidable)) {
                    (void)c1;
                    (void)c2;
                    /// Do not collide entities with themselves or two static entities
                    if (id1.getId() == id2.getId() || !(vel1 || vel2))
                        continue;
                    /// Do not make further check because entities are too far to collide
                    // if (abs(pos1.x - pos2.x) * 2 > (size1.x + size2.x)
                    //     && abs(pos1.z - pos2.z) * 2 > (size1.z + size2.z))
                    //     continue;

                    raylib::shapes::Rectangle rect1(
                        {pos1.x - size1.x / 2.f, pos1.z - size1.z / 2.f}, {size1.x, size1.z});
                    raylib::shapes::Rectangle rect2(
                        {pos2.x - size2.x / 2.f, pos2.z - size2.z / 2.f}, {size2.x, size2.z});

                    if (!rect1.checkCollision(rect2))
                        continue;
                    ::Rectangle collideRect = rect1.getCollision(rect2).getRaylibRectangle();
                    Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                        writer << "Testing collision with " << id1.getId() << " and " << id2.getId() << ": pos ("
                               << pos1.x << ", " << pos1.z << ") and (" << pos2.x << ", " << pos2.y
                               << ") collideRect: (" << collideRect.x << ", " << collideRect.y << ", "
                               << collideRect.width << ", " << collideRect.height << ")";
                    });
                    float firstMovePercent = (vel1 && vel2) ? 0.5f : (vel1) ? 1.f : 0.f;
                    Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                        writer << "First entity will take " << firstMovePercent * 100
                               << "% of the collision resolution";
                    });
                    if (firstMovePercent > 0.f) {
                        pos1.x += collideRect.height * firstMovePercent * ((collideRect.x < pos1.x) ? 1 : -1);
                        pos1.z += collideRect.width * firstMovePercent * ((collideRect.y < pos1.z) ? 1 : -1);
                    }
                    if ((1 - firstMovePercent) > 0.f) {
                        firstMovePercent = 1 - firstMovePercent;
                        if (collideRect.height < collideRect.width)
                            pos2.x += collideRect.height * firstMovePercent * ((collideRect.x < pos2.x) ? 1 : -1);
                        else
                            pos2.z += collideRect.width * firstMovePercent * ((collideRect.y < pos2.z) ? 1 : -1);

                        Logger::logger.log(Logger::Severity::Debug, [&](std::ostream &writer) {
                            writer << "Second entity new pos after move of "
                                   << collideRect.width * firstMovePercent * ((collideRect.y < pos2.z) ? 1 : -1)
                                   << " is " << pos2.z;
                        });
                    }
                }
            }
        }
    };

} // namespace game

#endif /* !TEMP_HPP_ */
