/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** GameWorld
*/

#include "game/Game.hpp"
#include "game/worlds/Worlds.hpp"
#include "raylib/core/Camera3D.hpp"

namespace game
{
    void Worlds::loadGameWorld(game::Game &game, raylib::core::Camera3D &camera) { game.setup(camera); }
} // namespace game
