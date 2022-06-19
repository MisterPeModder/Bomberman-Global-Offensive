/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** AI Updating
*/

#ifndef GAME_SYSTEMS_AI_UPDATE_HPP_
#define GAME_SYSTEMS_AI_UPDATE_HPP_

#include "ecs/System.hpp"

namespace game::systems
{
    struct AiUpdate : public ecs::System {
        void run(ecs::SystemData data) override final;
    };
} // namespace game::systems

#endif // !defined(GAME_SYSTEMS_AI_UPDATE_HPP_)
