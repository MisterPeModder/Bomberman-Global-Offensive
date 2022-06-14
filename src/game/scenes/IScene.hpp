/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** IScene
*/

#ifndef GAME_SCENES_ISCENE_HPP_
#define GAME_SCENES_ISCENE_HPP_

#include "ecs/World.hpp"
#include "game/Game.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    class IScene {
      public:
        virtual ~IScene() = default;

        /// Call the scene's drawFrame function
        virtual void drawFrame() = 0;

        /// Gets the scene's mutable world object
        virtual ecs::World &getWorld() = 0;

        /// Gets the scene's immutable world object
        virtual const ecs::World &getWorld() const = 0;
    };
} // namespace game

#endif /* !GAME_SCENES_ISCENE_HPP_ */
