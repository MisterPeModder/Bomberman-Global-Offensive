/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** AWorld
*/

#ifndef GAME_WORLDS_AWORLD_HPP_
#define GAME_WORLDS_AWORLD_HPP_

#include "ecs/World.hpp"
#include "game/worlds/IWorld.hpp"

namespace game
{
    class AWorld : public game::IWorld {
      public:
        AWorld(ecs::World &world);
        ~AWorld();
        void setCamera(raylib::core::Camera3D &camera) override;
        void drawFrame(const raylib::core::Camera3D &camera) override;

      protected:
        ecs::World &_world;
    };
} // namespace game

#endif /* !GAME_WORLDS_AWORLD_HPP_ */
