/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Global ECS tests
*/

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Timer.hpp"

#include <chrono>
#include <gtest/gtest.h>
#include <thread>

using namespace std::chrono_literals;

struct Position : public ecs::Component {
    float x, y;

    Position(float px, float py) : x(px), y(py) {}
};

struct Velocity : public ecs::Component {
    float x, y;

    Velocity(float vx, float vy) : x(vx), y(vy) {}
};

struct Movement : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        float seconds = data.getResource<ecs::Timer>().elapsed();

        for (auto [pos, vel] : ecs::join(data.getStorage<Position>(), data.getStorage<Velocity>())) {
            // no friction here, just plain old perpertual motion
            pos.x += vel.x * seconds;
            pos.y += vel.y * seconds;
        }
    }
};

struct Gravity : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        for (auto [vel] : ecs::join(data.getStorage<Velocity>()))
            vel.y = 9.8;
    }
};

TEST(ecs, motionWithoutGravity)
{
    ecs::World world;

    world.addResource<ecs::Timer>();
    world.addSystem<Movement>();

    auto immovable = world.addEntity().with<Position>(42.f, 42.f).build();
    auto movable = world.addEntity().with<Position>(0.f, 100.f).with<Velocity>(-400.f, 200.f).build();

    // Without gravity

    std::this_thread::sleep_for(50ms);
    double elapsed = world.getResource<ecs::Timer>().elapsed();

    world.runSystems();

    EXPECT_FLOAT_EQ(world.getStorage<Position>()[immovable.getId()].x, 42.f);
    EXPECT_FLOAT_EQ(world.getStorage<Position>()[immovable.getId()].y, 42.f);

    EXPECT_NEAR(world.getStorage<Position>()[movable.getId()].x, -400.f * elapsed, 1);
    EXPECT_NEAR(world.getStorage<Position>()[movable.getId()].y, 100.f + 200.f * elapsed, 1);
}

TEST(ecs, motionWithGravity)
{
    ecs::World world;

    world.addResource<ecs::Timer>();
    world.addSystem<Movement>();
    world.addSystem<Gravity>();

    auto immovable = world.addEntity().with<Position>(42.f, 42.f).build();
    auto movable = world.addEntity().with<Position>(0.f, 100.f).with<Velocity>(-400.f, 200.f).build();

    // Without gravity

    std::this_thread::sleep_for(50ms);
    double elapsed = world.getResource<ecs::Timer>().elapsed();

    // The gravity system must run before the movement system
    world.runSystem<Gravity>();
    world.runSystem<Movement>();

    EXPECT_FLOAT_EQ(world.getStorage<Position>()[immovable.getId()].x, 42.f);
    EXPECT_FLOAT_EQ(world.getStorage<Position>()[immovable.getId()].y, 42.f);

    EXPECT_NEAR(world.getStorage<Position>()[movable.getId()].x, -400.f * elapsed, 1);
    EXPECT_NEAR(world.getStorage<Position>()[movable.getId()].y, 100.f + 9.8f * elapsed, 1);

    EXPECT_FLOAT_EQ(world.getStorage<Velocity>()[movable.getId()].x, -400.f);
    EXPECT_FLOAT_EQ(world.getStorage<Velocity>()[movable.getId()].y, 9.8f);
}
