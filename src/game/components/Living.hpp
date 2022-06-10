/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Living
*/

#ifndef GAME_COMPONENTS_LIVING_HPP_
#define GAME_COMPONENTS_LIVING_HPP_

#include "ecs/Component.hpp"

namespace game
{
    struct Living : public ecs::Component {
        size_t hp;
        size_t hpMax;
        Living(size_t php = 1, size_t phpMax = 1) : hp(php), hpMax(phpMax) {}
        Living(size_t php = 1) : hp(php), hpMax(php) {}
    };
} // namespace game

#endif /* !GAME_COMPONENTS_LIVING_HPP_ */
