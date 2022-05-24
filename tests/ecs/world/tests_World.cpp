/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Basic tests for the Entity Component System
*/

#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/resource/Entities.hpp"
#include "ecs/resource/Resource.hpp"

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std::string_literals;

struct Data : public ecs::System, public ecs::Resource {
    std::string str;
    int someNumber;
    std::vector<std::string> &nonTrivialRef;

    Data(std::string s, int num, std::vector<std::string> &ref) : str(s), someNumber(num), nonTrivialRef(ref) {}

    virtual void run(ecs::SystemData) override final {}
};

struct Count : public ecs::Resource {
    int count = 0;
};

struct CountingSystem : public ecs::System {
    virtual void run(ecs::SystemData data) override final { data.getResource<Count>().count += 1; }
};

/// CountingSystem 2: Electric Boogaloo
struct CountingSystem2 : public ecs::System {
    virtual void run(ecs::SystemData data) override final { data.getResource<Count>().count += 2; }
};

TEST(World, addResource)
{
    ecs::World world;
    std::vector<std::string> strings{"This"s, "is"s, "a"s, "test"s};

    Data &ds(world.addResource<Data>("some string", 42, strings));

    EXPECT_EQ(ds.str, "some string");
    EXPECT_EQ(ds.someNumber, 42);
    EXPECT_EQ(ds.nonTrivialRef, strings);

    // May not register the same type twice
    ASSERT_THROW(world.addResource<Data>("???", -1, strings), std::logic_error);

    // The Entities ressource is always registered
    ASSERT_THROW(world.addResource<ecs::Entities>(), std::logic_error);
}

TEST(World, runSystem)
{
    ecs::World world;
    Count &count = world.addResource<Count>();

    // May not run unregistered systems
    ASSERT_THROW(world.runSystem<CountingSystem>(), std::logic_error);

    world.addSystem<CountingSystem>();

    EXPECT_EQ(count.count, 0);
    world.runSystem<CountingSystem>();
    EXPECT_EQ(count.count, 1);
    world.runSystem<CountingSystem>();
    EXPECT_EQ(count.count, 2);
}

TEST(World, runSystems)
{
    ecs::World world;
    Count &count = world.addResource<Count>();

    world.addSystem<CountingSystem>();
    world.addSystem<CountingSystem2>();

    EXPECT_EQ(count.count, 0);
    world.runSystem<CountingSystem>();
    EXPECT_EQ(count.count, 1);
    world.runSystems();
    EXPECT_EQ(count.count, 4);
}
