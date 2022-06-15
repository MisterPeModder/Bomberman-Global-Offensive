/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameScene
*/

#ifndef GAME_SCENES_GAMESCENES_HPP_
#define GAME_SCENES_GAMESCENES_HPP_

#include "ecs/World.hpp"
#include "game/Game.hpp"
#include "game/scenes/AScene.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class GameScene : public AScene {
      public:
        GameScene() : _game(_world, game::Game::Parameters(2)) { _game.setup(); }

        GameScene(game::Game::Parameters parameters) : _game(_world, parameters) { _game.setup(); }

        ~GameScene() = default;

        void drawFrame() override final { _game.drawFrame(); }

      private:
        Game _game;
    };
} // namespace game

#endif
