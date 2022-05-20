/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Generic Entity
*/

#ifndef ECS_ENTITY_HPP_
#define ECS_ENTITY_HPP_

#include <cstddef>

namespace ecs
{
    class Entities;

    /// A holder of components.
    class Entity {
      public:
        using Index = std::size_t;
        using Generation = std::size_t;

        constexpr Index getId() const noexcept { return this->_id; }
        constexpr Generation getGeneration() const noexcept { return this->_generation; }

      private:
        Index _id;
        Generation _generation;

        inline constexpr Entity(Index id, Generation generation = 0) : _id(id), _generation(generation) {}

        // Only the `Entities` World Resource may create entities.
        friend Entities;
    };
} // namespace ecs

#endif // !defined(ECS_ENTITY_HPP_)
