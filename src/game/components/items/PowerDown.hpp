/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PowerDOwn
*/

#ifndef GAME_COMPONENTS_ITEMS_POWERDOWN_HPP_
#define GAME_COMPONENTS_ITEMS_POWERDOWN_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"

namespace game::components
{
    /// PowerUp component
    struct PowerDown final : public ecs::Component {
        /// Construct a new PowerUp marker.
        PowerDown(){};
    };
} // namespace game::components

SET_COMPONENT_STORAGE(game::components::PowerDown, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_ITEMS_POWERDOWN_HPP_ */
