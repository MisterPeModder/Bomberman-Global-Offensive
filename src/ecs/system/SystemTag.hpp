/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - System group tag
*/

#ifndef ECS_SYSTEM_SYSTEM_TAG_HPP_
#define ECS_SYSTEM_SYSTEM_TAG_HPP_

#include <concepts>
#include <typeindex>
#include <vector>

namespace ecs
{
    class System;

    /// A group of @ref System types.
    class SystemTag {
      public:
        /// Constructs an empty system tag.
        SystemTag();

        /// Copy constructor.
        SystemTag(SystemTag const &) = default;

        /// Move constructor.
        SystemTag(SystemTag &&) = default;

        /// Adds the given System types to this tag.
        ///
        /// @tparam First The first system type.
        /// @tparam Rest The other system types to add (optional).
        ///
        /// @returns This tag, to allow chaining.
        template <std::derived_from<System> First, std::derived_from<System>... Rest> SystemTag &add()
        {
            this->_types.emplace_back(typeid(First));
            (this->_types.emplace_back(typeid(Rest)), ...);
            return *this;
        }

        /// Adds all the system types from the given source, duplicate types are not added.
        ///
        /// @param source The source.
        ///
        /// @returns This tag, to allow chaining.
        SystemTag &add(SystemTag const &source);

      private:
        std::vector<std::type_index> _types;

        /// Only Worlds should be able to access the tag's internals.
        friend class World;
    };
} // namespace ecs

#endif // !defined(ECS_SYSTEM_SYSTEM_TAG_HPP_)
