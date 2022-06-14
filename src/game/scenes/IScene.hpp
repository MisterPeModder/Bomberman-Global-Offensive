/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** IScene
*/

#ifndef GAME_SCENES_ISCENE_HPP_
#define GAME_SCENES_ISCENE_HPP_

#include "game/Game.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class IScene {
      public:
        virtual ~IScene() = default;
        virtual void setCamera(raylib::core::Camera3D &camera) = 0;
        virtual void drawFrame(const raylib::core::Camera3D &camera) = 0;
    };
} // namespace game

#endif /* !GAME_SCENES_ISCENE_HPP_ */
