/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Tests the black magic
*/

#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/resource/Entities.hpp"
#include "ecs/storage/MapStorage.hpp"
#include "ecs/storage/MarkerStorage.hpp"

#include <array>
#include <concepts>
#include <functional>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <ranges>

using ::testing::Contains;
using ::testing::Not;

struct Position : public ecs::Component {
    float x;
    float y;

    Position(float px, float py) : x(px), y(py) {}
};

struct Velocity : public ecs::Component {
    float x;
    float y;

    Velocity(float px, float py) : x(px), y(py) {}
};

struct Marker : public ecs::Component {};
SET_COMPONENT_STORAGE(Marker, ecs::MarkerStorage);

struct Marker2 : public ecs::Component {};
SET_COMPONENT_STORAGE(Marker2, ecs::MarkerStorage);

// JoinIter must be an input iterator
static_assert(std::input_iterator<ecs::JoinIter<ecs::MapStorage<Position>>>);
static_assert(std::input_iterator<ecs::JoinIter<ecs::MapStorage<Position>, ecs::MarkerStorage<Marker>>>);

// Join must be iterable
static_assert(std::ranges::range<ecs::Join<ecs::MapStorage<Position>>>);
static_assert(std::ranges::range<ecs::Join<ecs::MapStorage<Position>, ecs::MarkerStorage<Marker>>>);

static_assert(ecs::Joinable<ecs::MapStorage<Position>>);
static_assert(ecs::Joinable<ecs::MarkerStorage<Marker>>);

class TestSystem : public ecs::System {
  public:
    TestSystem(std::function<void(ecs::SystemData)> &&func) : _func(func) {}

    void run(ecs::SystemData data) override final { this->_func(data); }

  private:
    std::function<void(ecs::SystemData)> _func;
};

struct RemovingSystem : public ecs::System {
    void run(ecs::SystemData data) override final
    {
        auto &entities = data.getResource<ecs::Entities>();

        for (auto [entity] : ecs::join(entities)) {
            if (entity.getId() % 2 != 0)
                entities.kill(entity);
        }
    }
};

static void createWorld(ecs::World &world)
{
    for (std::size_t i = 0; i < 100; ++i)
        world.addEntity().with<Position>(21.0f, 42.0f).with<Marker>().build();
    for (std::size_t i = 0; i < 100; ++i)
        world.addEntity().with<Position>(21.0f, 84.0f).build();
    for (std::size_t i = 0; i < 100; ++i)
        world.addEntity().with<Marker>().build();
    for (std::size_t i = 0; i < 100; ++i) {
        if (i % 2)
            world.addEntity().with<Position>(67.0f, 23.0f).with<Marker>().build();
        else
            world.addEntity().with<Marker>().build();
    }
}

TEST(Join, positionsAndMarkers)
{
    ecs::World world;

    createWorld(world);
    world.addSystem<TestSystem>([](ecs::SystemData data) {
        // specifying exact types to prevent unwanted implicit conversions,
        // use of 'auto' is fine (and recommended) in normal code.

        ecs::MapStorage<Position> &positions = data.getStorage<Position>();
        ecs::MarkerStorage<Marker> &markers = data.getStorage<Marker>();

        ecs::Join<ecs::MapStorage<Position>, ecs::MarkerStorage<Marker>> both = ecs::join(positions, markers);

        std::size_t i = 0;

        for (std::tuple<Position &, Marker &> v : both) {
            if (i < 100) {
                EXPECT_FLOAT_EQ(std::get<0>(v).x, 21.0f) << "x coordinate for entity " << i << " is invalid";
                EXPECT_FLOAT_EQ(std::get<0>(v).y, 42.0f) << "y coordinate for entity " << i << " is invalid";
            } else {
                EXPECT_FLOAT_EQ(std::get<0>(v).x, 67.0f) << "x coordinate for entity " << i << " is invalid";
                EXPECT_FLOAT_EQ(std::get<0>(v).y, 23.0f) << "y coordinate for entity " << i << " is invalid";
            }
            ++i;
        }
        EXPECT_EQ(i, 150);
    });
    world.runSystem<TestSystem>();
}

TEST(Join, positionsOnly)
{
    ecs::World world;

    createWorld(world);
    world.addSystem<TestSystem>([](ecs::SystemData data) {
        auto &positions = data.getStorage<Position>();
        std::size_t i = 0;

        for (auto [pos] : ecs::join(positions)) {
            if (i < 100) {
                EXPECT_FLOAT_EQ(pos.x, 21.0f) << "x coordinate for entity " << i << " is invalid";
                EXPECT_FLOAT_EQ(pos.y, 42.0f) << "y coordinate for entity " << i << " is invalid";
            } else if (i < 200) {
                EXPECT_FLOAT_EQ(pos.x, 21.0f) << "x coordinate for entity " << i << " is invalid";
                EXPECT_FLOAT_EQ(pos.y, 84.0f) << "y coordinate for entity " << i << " is invalid";
            } else {
                EXPECT_FLOAT_EQ(pos.x, 67.0f) << "x coordinate for entity " << i << " is invalid";
                EXPECT_FLOAT_EQ(pos.y, 23.0f) << "y coordinate for entity " << i << " is invalid";
            }
            ++i;
        }
        EXPECT_EQ(i, 250);
    });
    world.runSystem<TestSystem>();
}

TEST(Join, optionalPositionsWithMarkers)
{
    ecs::World world;

    createWorld(world);
    world.addSystem<TestSystem>([](ecs::SystemData data) {
        auto optionalPositions = ecs::maybe(data.getStorage<Position>());
        auto &markers = data.getStorage<Marker>();

        std::size_t withPos = 0;
        std::size_t withoutPos = 0;

        for (auto [pos, _] : ecs::join(optionalPositions, markers)) {
            if (pos) {
                if (withPos < 100) {
                    EXPECT_FLOAT_EQ(pos->x, 21.0f) << "x coordinate for entity " << withPos << " is invalid";
                    EXPECT_FLOAT_EQ(pos->y, 42.0f) << "y coordinate for entity " << withPos << " is invalid";
                }
                ++withPos;
            } else {
                ++withoutPos;
            }
        }
        EXPECT_EQ(withPos, 150);
        EXPECT_EQ(withoutPos, 150);
    });
    world.runSystem<TestSystem>();
}

TEST(Join, optionalSkipDead)
{
    ecs::World world;

    createWorld(world);

    std::array<ecs::Entity::Index, 5> blacklist{1, 2, 42, 128, 84};

    // remove some entities
    {
        auto &entities = world.getResource<ecs::Entities>();

        for (auto id : blacklist)
            entities.kill(entities.get(id));
    }
    world.maintain();
    world.addSystem<TestSystem>([&blacklist](ecs::SystemData data) {
        auto optionalPositions = ecs::maybe(data.getStorage<Position>());
        auto &entities = data.getResource<ecs::Entities>();

        for (auto [pos, entity] : ecs::join(optionalPositions, entities)) {
            EXPECT_THAT(blacklist, Not(Contains(entity.getId())));
        }
    });
    world.runSystem<TestSystem>();
}

/// Testing the way optional joins work with missing values at the end.
TEST(Join, optionalAlternativeOrdering)
{
    ecs::World world;

    world.addEntity().with<Position>(1.0f, 2.0f).with<Marker>().build();
    world.addEntity().with<Position>(3.0f, 4.0f).with<Marker>().build();
    world.addEntity().with<Position>(5.0f, 6.0f).build();
    world.addEntity().with<Position>(7.0f, 8.0f).build();

    world.addSystem<TestSystem>([](ecs::SystemData data) {
        auto optionalMarkers = ecs::maybe(data.getStorage<Marker>());
        auto &positions = data.getStorage<Position>();

        auto join = ecs::join(optionalMarkers, positions);
        auto iter = join.begin();

        auto [m1, p1] = *iter;
        auto [m2, p2] = *(++iter);
        auto [m3, p3] = *(++iter);
        auto [m4, p4] = *(++iter);

        EXPECT_TRUE(m1 != nullptr);
        EXPECT_FLOAT_EQ(p1.x, 1.0f);
        EXPECT_FLOAT_EQ(p1.y, 2.0f);

        EXPECT_TRUE(m2 != nullptr);
        EXPECT_FLOAT_EQ(p2.x, 3.0f);
        EXPECT_FLOAT_EQ(p2.y, 4.0f);

        EXPECT_TRUE(m3 == nullptr);
        EXPECT_FLOAT_EQ(p3.x, 5.0f);
        EXPECT_FLOAT_EQ(p3.y, 6.0f);

        EXPECT_TRUE(m4 == nullptr);
        EXPECT_FLOAT_EQ(p4.x, 7.0f);
        EXPECT_FLOAT_EQ(p4.y, 8.0f);
    });
    world.runSystem<TestSystem>();
}

TEST(Join, optionalMissingComponent)
{
    ecs::World world;

    world.addStorage<Marker>();

    world.addEntity().with<Position>(5.0f, 6.0f).build();
    world.addEntity().with<Position>(7.0f, 8.0f).build();

    world.addSystem<TestSystem>([](ecs::SystemData data) {
        auto optionalMarkers = ecs::maybe(data.getStorage<Marker>());
        auto &positions = data.getStorage<Position>();

        auto join = ecs::join(optionalMarkers, positions);
        auto iter = join.begin();

        auto [m1, p1] = *iter;
        auto [m2, p2] = *(++iter);

        EXPECT_TRUE(m1 == nullptr);
        EXPECT_FLOAT_EQ(p1.x, 5.0f);
        EXPECT_FLOAT_EQ(p1.y, 6.0f);

        EXPECT_TRUE(m2 == nullptr);
        EXPECT_FLOAT_EQ(p2.x, 7.0f);
        EXPECT_FLOAT_EQ(p2.y, 8.0f);
    });
    world.runSystem<TestSystem>();
}

TEST(Join, midLoopRemovals)
{
    ecs::World world;

    createWorld(world);
    world.addEntity().with<Marker2>().with<Velocity>(0.f, 0.f).build();

    world.addSystem<RemovingSystem>();
    world.runSystems();
    world.maintain();

    auto &entities = world.getResource<ecs::Entities>();
    auto &markers = world.getStorage<Marker>();

    EXPECT_TRUE(entities.isAlive(entities.get(0)));
    EXPECT_FALSE(entities.isAlive(entities.get(1)));
    EXPECT_TRUE(entities.isAlive(entities.get(2)));
    EXPECT_FALSE(entities.isAlive(entities.get(3)));
    EXPECT_TRUE(entities.isAlive(entities.get(4)));
    EXPECT_FALSE(entities.isAlive(entities.get(5)));

    EXPECT_TRUE(markers.contains(entities.get(0).getId()));
    EXPECT_FALSE(markers.contains(entities.get(1).getId()));

    EXPECT_EQ(world.addEntity().build().getId(), 1);
    EXPECT_EQ(world.addEntity().build().getId(), 3);
}
