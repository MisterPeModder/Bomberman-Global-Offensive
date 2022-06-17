/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** UseCheck
*/

#ifndef GAME_COMPONENTS_USECHECK_HPP_
#define GAME_COMPONENTS_USECHECK_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct UseCheck : public ecs::Component {
        bool used;

        UseCheck(bool pUseCheck = false) : used(pUseCheck) {}
    };
} // namespace game::components

#endif
