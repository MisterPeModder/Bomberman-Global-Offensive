/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** BombNoClip
*/

#include "BombNoClip.hpp"

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
        return enabled && bombPos.x == static_cast<unsigned int>(std::round(entityPosition.x))
            && bombPos.y == static_cast<unsigned int>(std::round(entityPosition.z));
    }
} // namespace game::components
