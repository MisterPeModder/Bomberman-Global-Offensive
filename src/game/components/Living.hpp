/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Living
*/

#ifndef GAME_COMPONENTS_LIVING_HPP_
#define GAME_COMPONENTS_LIVING_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct Living : public ecs::Component {
        size_t hp;
        size_t hpMax;
        Living(size_t php, size_t phpMax) : hp(php), hpMax(phpMax) {}
        Living(size_t php = 1) : hp(php), hpMax(php) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_LIVING_HPP_ */
