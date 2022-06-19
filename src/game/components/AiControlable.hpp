/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** AiControlable
*/

#ifndef GAME_COMPONENTS_AI_CONTROLABLE_HPP_
#define GAME_COMPONENTS_AI_CONTROLABLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/System.hpp"

#include "raylib/core/Vector2.hpp"

#include <deque>

namespace game::components
{
    /// Entity controllable by scripts
    struct AiControlable : public ecs::Component {
        std::deque<raylib::core::Vector2f> path;

        void pathFind(raylib::core::Vector2f pos, ecs::Entity self, ecs::SystemData data);
    };
} // namespace game::components

#endif // !defined(GAME_COMPONENTS_AI_CONTROLABLE_HPP_)
