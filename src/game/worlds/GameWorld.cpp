/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameWorld
*/

#include "ecs/Entity.hpp"
#include "ecs/Storage.hpp"
#include "ecs/System.hpp"
#include "game/Game.hpp"
#include "raylib/core/Color.hpp"
#include "util/util.hpp"
#include "game/worlds/Worlds.hpp"

namespace game
{
    void Worlds::loadGameWorld(game::Game &game, raylib::core::Camera3D &camera)
    {
        game.setup(camera);
    }
} // namespace game
