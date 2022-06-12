/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Worlds
*/

#ifndef GAME_WORLDS_WORLDS_HPP_
#define GAME_WORLDS_WORLDS_HPP_

#include "game/Game.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class IWorld {
      public:
        virtual ~IWorld() = default;
        virtual void setCamera(raylib::core::Camera3D &camera) = 0;
        virtual void drawFrame(const raylib::core::Camera3D &camera) = 0;
    };
} // namespace game

#endif /* !WORLDS_HPP_ */
