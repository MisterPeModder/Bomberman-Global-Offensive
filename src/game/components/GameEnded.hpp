/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** GameEnded
*/

#ifndef GAME_COMPONENTS_GAMEENDED_HPP_
#define GAME_COMPONENTS_GAMEENDED_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct GameEnded : public ecs::Component {
        bool gameEnded;
        double endTime;

        GameEnded(bool pGameEnded = false) : gameEnded(pGameEnded), endTime(0.0) {}
    };
} // namespace game::components

#endif
