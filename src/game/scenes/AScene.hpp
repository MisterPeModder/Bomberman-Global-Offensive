/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** AScene
*/

#ifndef GAME_WORLDS_ASCENES_HPP_
#define GAME_WORLDS_ASCENES_HPP_

#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "game/scenes/IScene.hpp"
#include "raylib/core/Camera2D.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class AScene : public game::IScene {
      public:
        AScene();
        ~AScene();
        virtual void setupWorld() override;
        virtual void drawFrame() override;
        ecs::World &getWorld() override final;
        const ecs::World &getWorld() const override final;

      protected:
        ecs::World _world;
        raylib::core::Camera2D _defaultCamera2D;
        raylib::core::Camera3D _defaultCamera3D;
        ecs::SystemTag _background2D;
        ecs::SystemTag _global2D;
        ecs::SystemTag _global3D;
        ecs::SystemTag _globalNoDraw;
    };
} // namespace game

#endif /* !GAME_WORLDS_ASCENES_HPP_ */
