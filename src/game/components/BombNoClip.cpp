/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** BombNoClip
*/

#include "BombNoClip.hpp"
#include "game/Game.hpp"
#include "game/systems/Collision.hpp"
#include "raylib/shapes/Rectangle.hpp"

namespace game::components
{
    BombNoClip::BombNoClip() : bombPos(0, 0), enabled(false) {}

    void BombNoClip::setBombPosition(raylib::core::Vector2u pBombPos)
    {
        bombPos = pBombPos;
        enabled = true;
    }

    bool BombNoClip::matchEntityPosition(raylib::core::Vector3f entityPosition, raylib::core::Vector3f entitySize)
    {
        raylib::shapes::Rectangle collideRect;

        return game::systems::Collision::getCollideRect(collideRect, entityPosition, entitySize,
            {static_cast<float>(bombPos.x), 0.f, static_cast<float>(bombPos.y)}, {1.f, 1.f, 1.f});
    }
} // namespace game::components
