/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Destructible
*/

#ifndef GAME_COMPONENTS_DESTRUCTIBLE_HPP_
#define GAME_COMPONENTS_DESTRUCTIBLE_HPP_

#include "ecs/Component.hpp"

namespace game
{
    struct Destructible final : public ecs::Component {
        bool destructed;

        Destructible(bool pdestructed) : destructed(pdestructed){};
    };
} // namespace game

#endif /* !GAME_COMPONENTS_DESTRUCTIBLE_HPP_ */
