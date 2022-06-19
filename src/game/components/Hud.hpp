/*
** EPITECH PROJECT, 2022
** Bomberman-Global-Offensive
** File description:
** Hud
*/

#ifndef HUD_COMPONENTS_HPP_
#define HUD_COMPONENTS_HPP_

#include "Player.hpp"
#include "ecs/Component.hpp"
#include "ecs/System.hpp"
#include "game/components/Position.hpp"

namespace game::components
{
    /// Cube color component
    struct Hud : public ecs::Component {
        ///
        Hud(Player owner);
    };
} // namespace game::components

#endif /*!HUD_COMPONENTS_HPP_*/
