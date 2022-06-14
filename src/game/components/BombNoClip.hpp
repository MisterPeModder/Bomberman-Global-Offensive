/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** BombNoClip
*/

#ifndef GAME_COMPONENTS_BOMBNOCLIP_HPP_
#define GAME_COMPONENTS_BOMBNOCLIP_HPP_

#include <cmath>
#include "ecs/Component.hpp"
#include "raylib/core/Vector3.hpp"

namespace game::components
{
    struct BombNoClip : public ecs::Component {
        raylib::core::Vector2u bombPos;
        bool enabled;

        BombNoClip() : bombPos(0, 0), enabled(false) {}
        BombNoClip(raylib::core::Vector2u pBombPos) : bombPos(pBombPos), enabled(false) {}

        void setBombPosition(raylib::core::Vector2u pBombPos)
        {
            bombPos = pBombPos;
            enabled = true;
        }

        bool matchEntityPosition(raylib::core::Vector3f entityPosition)
        {
            return enabled && bombPos.x == static_cast<unsigned int>(std::round(entityPosition.x))
                && bombPos.y == static_cast<unsigned int>(std::round(entityPosition.z));
        }
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_BOMBNOCLIP_HPP_ */
