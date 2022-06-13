/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** AScene
*/

#ifndef GAME_WORLDS_ASCENES_HPP_
#define GAME_WORLDS_ASCENES_HPP_

#include "ecs/World.hpp"
#include "game/scenes/IScene.hpp"

namespace game
{
    class AScene : public game::IScene {
      public:
        AScene();
        ~AScene();
        void setCamera(raylib::core::Camera3D &camera) override;
        void drawFrame(const raylib::core::Camera3D &camera) override;

      protected:
        ecs::World _world;
    };
} // namespace game

#endif /* !GAME_WORLDS_ASCENES_HPP_ */
