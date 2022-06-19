/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Draw FPS counter in debug mode
*/

#ifndef GAME_SYSTEM_DRAW_FPS_COUNTER_HPP_
#define GAME_SYSTEM_DRAW_FPS_COUNTER_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    struct DrawFpsCounter : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif // !defined(GAME_SYSTEM_DRAW_FPS_COUNTER_HPP_)
