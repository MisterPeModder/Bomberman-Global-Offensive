/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Global ECS tests
*/

#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "ecs/join.hpp"
#include "ecs/storage/MapStorage.hpp"
#include "ecs/storage/MarkerStorage.hpp"

#include <array>
#include <gtest/gtest.h>

struct Position : public ecs::Component {
    float x;
    float y;

    Position(float px, float py) : x(px), y(py) {}
};

struct Marker : public ecs::Component {
};
SET_COMPONENT_STORAGE(Marker, ecs::MarkerStorage);

// struct Velocity : public ecs::Component {
//     float x;
//     float y;
// };
// SET_COMPONENT_STORAGE(Velocity, ecs::MapStorage);

// struct Movement : public ecs::System {
//     void run(ecs::SystemData data) override final {

//     }
// };

struct Gravity : public ecs::System {
    float g;

    Gravity(float force) : g(force) {}

    void run(ecs::SystemData data) override final
    {
        auto &positions = data.getStorage<Position>();

        for (auto [pos] : ecs::join(positions)) {
            pos.y -= 1.0f;
        }
    }
};

TEST(ecs, gravity)
{
    ecs::World world;

    world.addSystem<Gravity>(9.1f);

    std::array<ecs::Entity, 3> entities{
        world.addEntity().with<Position>(2.0f, 1.0f).build(),
        world.addEntity().with<Position>(89.0f, 9.0f).with<Marker>().build(),
        world.addEntity().with<Position>(21.0f, 42.0f).with<Marker>().build(),
    };

    EXPECT_EQ(world.getStorage<Position>().size(), 3);

    ASSERT_NO_THROW(world.getStorage<Position>()[entities[0].getId()]);

    world.runSystems();

    ASSERT_FLOAT_EQ(world.getStorage<Position>()[entities[0].getId()].y, 0);
    ASSERT_FLOAT_EQ(world.getStorage<Position>()[entities[1].getId()].y, 8);
    ASSERT_FLOAT_EQ(world.getStorage<Position>()[entities[2].getId()].y, 41);
}
