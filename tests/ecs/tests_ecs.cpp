/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Basic tests for the Entity Component System
*/

#include "ecs/System.hpp"
#include "ecs/World.hpp"

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::string_literals;

struct DataSystem : public ecs::System {
    std::string str;
    int someNumber;
    std::vector<std::string> &nonTrivialRef;

    DataSystem(std::string s, int num, std::vector<std::string> &ref) : str(s), someNumber(num), nonTrivialRef(ref) {}

    virtual void run(ecs::EntityAccess &) override final {}
};

struct CountingSystem : public ecs::System {
    int runCount = 0;

    virtual void run(ecs::EntityAccess &) override final { ++runCount; }
};

/// CountingSystem 2: Electric Boogaloo
struct CountingSystem2 : public ecs::System {
    int runCount = 0;

    virtual void run(ecs::EntityAccess &) override final { runCount += 2; }
};

TEST(World, addSystem)
{
    ecs::World world;
    std::vector<std::string> strings{"This"s, "is"s, "a"s, "test"s};

    DataSystem &ds(world.addSystem<DataSystem>("some string", 42, strings));

    EXPECT_EQ(ds.str, "some string");
    EXPECT_EQ(ds.someNumber, 42);
    EXPECT_EQ(ds.nonTrivialRef, strings);

    // May not register the same type twice
    ASSERT_THROW(world.addSystem<DataSystem>("???", -1, strings), std::logic_error);
    ASSERT_NO_THROW(world.addSystem<CountingSystem>());
}

TEST(World, runSystem)
{
    ecs::World world;

    // May not run unregistered systems
    ASSERT_THROW(world.runSystem<CountingSystem>(), std::logic_error);

    // May not get unregistered systems instances
    ASSERT_THROW(world.getSystem<CountingSystem>(), std::logic_error);

    world.addSystem<CountingSystem>();

    EXPECT_EQ(world.getSystem<CountingSystem>().runCount, 0);
    world.runSystem<CountingSystem>();
    EXPECT_EQ(world.getSystem<CountingSystem>().runCount, 1);
    world.runSystem<CountingSystem>();
    EXPECT_EQ(world.getSystem<CountingSystem>().runCount, 2);
}

TEST(World, runSystems)
{
    ecs::World world;

    CountingSystem &counting(world.addSystem<CountingSystem>());
    CountingSystem2 &counting2(world.addSystem<CountingSystem2>());

    EXPECT_EQ(counting.runCount, 0);
    EXPECT_EQ(counting2.runCount, 0);
    world.runSystem<CountingSystem>();
    EXPECT_EQ(counting.runCount, 1);
    EXPECT_EQ(counting2.runCount, 0);
    world.runSystems();
    EXPECT_EQ(counting.runCount, 2);
    EXPECT_EQ(counting2.runCount, 2);
}
