/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameWorld
*/

#include "ecs/World.hpp"
#include "game/Game.hpp"
#include "game/worlds/IWorld.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class GameWorld : public IWorld {
      public:
        GameWorld(ecs::World &world) : _world(world), _game(world) { _game.setup(); }

        ~GameWorld() { _world.clear(); }

        void setCamera(raylib::core::Camera3D &camera) { _game.setCamera(camera); }

        void drawFrame(const raylib::core::Camera3D &camera) { _game.drawFrame(camera); }

      private:
        Game _game;
        ecs::World &_world;
    };
} // namespace game
