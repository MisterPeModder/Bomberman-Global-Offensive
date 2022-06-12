/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** MainWorld
*/

#ifndef GAME_WORLD_MAINWORLD_HPP_
#define GAME_WORLD_MAINWORLD_HPP_

#include "ecs/World.hpp"
#include "game/worlds/AWorld.hpp"

namespace game
{
    class MainWorld : public AWorld {
      public:
        MainWorld(ecs::World &world);
    };
} // namespace game

#endif /* !GAME_WORLD_MAINWORLD_HPP_ */
