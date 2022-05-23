/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Global ECS tests
*/

#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "ecs/SystemData.hpp"
#include "ecs/storage/TreeStorage.hpp"
#include "ecs/world/World.hpp"

#include <gtest/gtest.h>

struct Position : public ecs::Component {
    float x;
    float y;

    Position(float px, float py) : x(px), y(py) {}
};
SET_COMPONENT_STORAGE(Position, ecs::TreeStorage);

// struct Velocity : public ecs::Component {
//     float x;
//     float y;
// };
// SET_COMPONENT_STORAGE(Velocity, ecs::TreeStorage);

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

        for (auto &[entity, pos] : positions) {
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
        world.addEntity().with<Position>(89.0f, 9.0f).build(),
        world.addEntity().with<Position>(21.0f, 42.0f).build(),
    };

    EXPECT_EQ(world.getStorage<Position>().size(), 3);

    ASSERT_NO_THROW(world.getStorage<Position>()[entities[0]]);

    world.runSystems();

    ASSERT_FLOAT_EQ(world.getStorage<Position>()[entities[0]].y, 0);
    ASSERT_FLOAT_EQ(world.getStorage<Position>()[entities[1]].y, 8);
    ASSERT_FLOAT_EQ(world.getStorage<Position>()[entities[2]].y, 41);
}
