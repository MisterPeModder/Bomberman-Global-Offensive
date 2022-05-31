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

struct Marker : public ecs::Component {
};
SET_COMPONENT_STORAGE(Marker, ecs::MarkerStorage);

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
        auto optional_positions = ecs::maybe(data.getStorage<Position>());
        auto &markers = data.getStorage<Marker>();

        std::size_t withPos = 0;
        std::size_t withoutPos = 0;

        for (auto [pos, _] : ecs::join(optional_positions, markers)) {
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
            entities.erase(entities.get(id));
    }
    world.addSystem<TestSystem>([&blacklist](ecs::SystemData data) {
        auto optional_positions = ecs::maybe(data.getStorage<Position>());
        auto &entities = data.getResource<ecs::Entities>();

        for (auto [pos, entity] : ecs::join(optional_positions, entities)) {
            EXPECT_THAT(blacklist, Not(Contains(entity.getId())));
        }
    });
    world.runSystem<TestSystem>();
}
