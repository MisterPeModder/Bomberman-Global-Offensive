/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PowerUp
*/

#ifndef GAME_COMPONENTS_ITEMS_POWERUP_HPP_
#define GAME_COMPONENTS_ITEMS_POWERUP_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"

namespace game::components
{
    /// PowerUp component
    struct PowerUp final : public ecs::Component {
        /// Construct a new PowerUp marker.
        PowerUp(){};
    };
} // namespace game::components

SET_COMPONENT_STORAGE(game::components::PowerUp, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_ITEMS_POWERUP_HPP_ */
