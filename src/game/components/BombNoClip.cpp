/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** BombNoClip
*/

#include "BombNoClip.hpp"
#include "game/Game.hpp"

namespace game::components
{
    BombNoClip::BombNoClip() : bombPos(0, 0), enabled(false) {}

    void BombNoClip::setBombPosition(raylib::core::Vector2u pBombPos)
    {
        bombPos = pBombPos;
        enabled = true;
    }

    bool BombNoClip::matchEntityPosition(raylib::core::Vector3f entityPosition)
    {
        return enabled && bombPos == game::Game::worldPosToMapCell(entityPosition);
    }
} // namespace game::components
