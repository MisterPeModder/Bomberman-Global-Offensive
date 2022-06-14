/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** PowerDOwn
*/

#ifndef GAME_COMPONENTS_ITEMS_ACTIVABLE_HPP_
#define GAME_COMPONENTS_ITEMS_ACTIVABLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"

namespace game::components
{
    /// PowerUp component
    struct Activable final : public ecs::Component {
        /// Construct a new PowerUp marker.
        Activable(){};
    };
} // namespace game::components

SET_COMPONENT_STORAGE(game::components::Activable, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_ITEMS_ACTIVABLE_HPP_ */
