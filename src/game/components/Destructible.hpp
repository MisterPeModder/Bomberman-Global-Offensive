/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Destructible
*/

#ifndef GAME_COMPONENTS_DESTRUCTIBLE_HPP_
#define GAME_COMPONENTS_DESTRUCTIBLE_HPP_

#include "ecs/Component.hpp"
#include "ecs/Storage.hpp"

namespace game::components
{
    /// Destructible component
    struct Destructible final : public ecs::Component {
        /// Construct a new Destructible marker.
        Destructible(){};
    };
} // namespace game::components

// SET_COMPONENT_STORAGE(game::components::Destructible, ecs::MarkerStorage);

#endif /* !GAME_COMPONENTS_DESTRUCTIBLE_HPP_ */
