/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Generic Entity
*/

#ifndef ECS_ENTITY_HPP_
#define ECS_ENTITY_HPP_

#include <compare>
#include <cstddef>

namespace ecs
{
    class Entities;

    /// Encapsulates a index to an entity that may or may not exist.
    ///
    /// This class is trivially copiable because the components are not stored in this class.
    class Entity final {
      public:
        /// The id type.
        using Index = std::size_t;
        /// The generation type.
        using Generation = std::size_t;

        /// @returns The index of this entity.
        constexpr Index getId() const noexcept { return this->_id; }

        /// @returns The generation of this entity, alive entities always have a generation number that is equal or
        /// greater than one.
        constexpr Generation getGeneration() const noexcept { return this->_generation; }

        /// Entity index comparison. Generations are ignored.
        auto operator<=>(Entity const &other) const { return this->_id <=> other._id; }

      private:
        Index _id;
        Generation _generation;

        /// The Entity structure may only be constructed by builders.
        ///
        /// @param id The id.
        /// @param generation The generation.
        inline constexpr Entity(Index id, Generation generation) : _id(id), _generation(generation) {}

        // Only the `Entities` World Resource may create entities.
        friend Entities;
    };
} // namespace ecs

#endif // !defined(ECS_ENTITY_HPP_)
