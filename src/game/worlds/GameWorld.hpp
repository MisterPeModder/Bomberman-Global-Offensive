/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameWorld
*/

#ifndef GAME_WORLD_GAMEWORLD_HPP_
#define GAME_WORLD_GAMEWORLD_HPP_

#include "ecs/World.hpp"
#include "game/Game.hpp"
#include "game/worlds/AWorld.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class GameWorld : public AWorld {
      public:
        GameWorld(ecs::World &world) : AWorld(world), _game(world) { _game.setup(); }

        ~GameWorld() = default;

        void setCamera(raylib::core::Camera3D &camera) override final { _game.setCamera(camera); }

        void drawFrame(const raylib::core::Camera3D &camera) override final { _game.drawFrame(camera); }

      private:
        Game _game;
    };
} // namespace game

#endif
