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
        float screenId;

        ScreenId(float pScreenId) : screenId(pScreenId) {}
        ScreenId(int pScreenId) : screenId(static_cast<float>(pScreenId)) {}
    };
} // namespace game::components

#endif
