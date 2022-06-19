/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Smoke
*/

#ifndef GAME_COMPONENTS_SMOKE_HPP_
#define GAME_COMPONENTS_SMOKE_HPP_

#include "Identity.hpp"
#include "ecs/Component.hpp"

namespace game::components
{
    /// Bomb component
    struct Smoke : public ecs::Component {
        /// Radius of the smoke
        size_t radius;
        /// Id of the entity who the smoke is attached to.
        Identity::Id owner;

        /// Construct a new Smoke component.
        ///
        /// @param pOwner @ref owner.
        /// @param pRadius @ref radius
        Smoke(Identity::Id pOwner, size_t pRadius = 2) : radius(pRadius), owner(pOwner){};
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_SMOKE_HPP_ */
