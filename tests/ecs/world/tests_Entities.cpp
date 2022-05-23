/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** Tests for the Entities world resource
*/

#include <gtest/gtest.h>

#include "ecs/Entity.hpp"
#include "ecs/world/Entities.hpp"

TEST(Entities, base)
{
    ecs::Entities entities;

    ecs::Entity e1 = entities.create();
    ecs::Entity e2 = entities.create();
    ecs::Entity e3 = entities.create();

    EXPECT_EQ(e1.getId(), 0);
    EXPECT_EQ(e2.getId(), 1);
    EXPECT_EQ(e3.getId(), 2);
    EXPECT_EQ(e1.getGeneration(), 1);
    EXPECT_EQ(e2.getGeneration(), 1);
    EXPECT_EQ(e3.getGeneration(), 1);

    entities.erase(e2);
    entities.erase(e3);

    EXPECT_FALSE(entities.isAlive(e2));
    EXPECT_FALSE(entities.isAlive(e3));

    e2 = entities.create();

    EXPECT_EQ(e2.getId(), 1);
    EXPECT_EQ(e2.getGeneration(), 2);

    e1 = entities.get(0);
    ecs::Entity e4 = entities.get(3);

    EXPECT_TRUE(entities.isAlive(e1));
    EXPECT_FALSE(entities.isAlive(e4));
}
