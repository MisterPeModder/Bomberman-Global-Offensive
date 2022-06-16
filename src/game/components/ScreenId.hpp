/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** ScreenId
*/

#ifndef GAME_COMPONENTS_SCREENID_HPP_
#define GAME_COMPONENTS_SCREENID_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    struct ScreenId : public ecs::Component {
        int screenId;

        ScreenId(int pScreenId) : screenId(pScreenId) {}
        ScreenId(float pScreenId) : screenId(static_cast<int>(pScreenId)) {}
    };
} // namespace game::components

#endif
