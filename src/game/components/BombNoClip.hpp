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
        /// Current target bomb position (cell in map).
        raylib::core::Vector2u bombPos;
        /// If the bomb mustn't collide with the entity owning this component.
        bool enabled;

        /// Construct a new Bomb No Clip component
        BombNoClip();

        /// Change the target bomb position.
        ///
        /// @param pBombPos target bomb position.
        void setBombPosition(raylib::core::Vector2u pBombPos);

        /// Test if an entity position match the target bomb position.
        /// @note This is used to test rounded Vector3f with Vector2u more easily.
        ///
        /// @param entityPosition tested entity position.
        /// @return true If the entity is on the same cell than the targeted bomb.
        /// @return false If the entity is on another cell.
        bool matchEntityPosition(raylib::core::Vector3f entityPosition);
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_BOMBNOCLIP_HPP_ */
