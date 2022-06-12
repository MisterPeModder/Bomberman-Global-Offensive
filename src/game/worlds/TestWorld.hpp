/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** TestWorld
*/

#ifndef GAME_WORLD_TESTWORLD_HPP_
#define GAME_WORLD_TESTWORLD_HPP_

#include "ecs/World.hpp"
#include "game/worlds/AWorld.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class TestWorld : public AWorld {
      public:
        TestWorld(ecs::World &world);
        ~TestWorld();
    };
} // namespace game

#endif /* !TESTWORLD_HPP_ */
