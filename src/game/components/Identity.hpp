/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Identity
*/

#ifndef GAME_COMPONENT_IDENTITY_HPP_
#define GAME_COMPONENT_IDENTITY_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    /// Unique Identity component.
    struct Identity : public ecs::Component {
      public:
        /// Identifier data type.
        using Id = long long unsigned int;
        /// Unique id of the entity
        Id id;

        /// Create a new Identity component with a unique Identifier.
        Identity();

        /// Get the current
        static Id getCurrentId();

      private:
        static Id _currentId;
    };
} // namespace game::components

#endif /* !GAME_COMPONENT_IDENTITY_HPP_ */
