/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Destructible
*/

#ifndef GAME_COMPONENTS_DESTRUCTIBLE_HPP_
#define GAME_COMPONENTS_DESTRUCTIBLE_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct Destructible final : public ecs::Component {
        bool destructed;

        Destructible(bool pdestructed = false) : destructed(pdestructed){};
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_DESTRUCTIBLE_HPP_ */
