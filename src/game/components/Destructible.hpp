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
    /// Destructible component
    struct Destructible final : public ecs::Component {
        /// If the component is destroyed.
        bool destroyed;

        /// Construct a new Destructible component.
        ///
        /// @param pdestroyed @ref destroyed.
        Destructible(bool pdestroyed = false) : destroyed(pdestroyed){};
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_DESTRUCTIBLE_HPP_ */
