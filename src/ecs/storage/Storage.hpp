/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - The Component Storage Trait
*/

#ifndef ECS_STORAGE_HPP_
#define ECS_STORAGE_HPP_

#include "ecs/Entity.hpp"

#include <concepts>
#include <iterator>

namespace ecs
{
    /// used to declare a virtual destructor on all Storage implementations.
    class BaseStorage {
      public:
        ~BaseStorage() = default;
    };

    /// The Compoonent storage trait.
    ///
    /// @note The iterators supplied by storages @b must yield their entity-component pair in increasing order of entity
    /// index.
    template <typename S>
    concept Storage = std::default_initializable<S> && std::derived_from<S, BaseStorage> && requires(
        S &storage, Entity entity)
    {
        typename S::Component;
        typename S::Iterator;
        typename S::ConstIterator;

        // required methods, we cannot test for emplace()
        storage.erase(entity);

        // the iterators must have a value type of pair<Entity, Component>
        requires std::same_as<typename S::Iterator::value_type, std::pair<const Entity, typename S::Component>>;
        requires std::same_as<typename S::ConstIterator::value_type, std::pair<const Entity, typename S::Component>>;

        // the iterators must satisfy `LegacyForwardIterator`.
        requires std::forward_iterator<typename S::Iterator>;
        requires std::forward_iterator<typename S::ConstIterator>;

        // clang-format off
        { storage.begin() } noexcept -> std::same_as<typename S::Iterator>;
        { storage.cbegin() } noexcept -> std::same_as<typename S::ConstIterator>;

        { storage.end() } noexcept -> std::same_as<typename S::Iterator>;
        { storage.cend() } noexcept -> std::same_as<typename S::ConstIterator>;
        // clang-format on
    };
} // namespace ecs

#endif // !defined(ECS_STORAGE_HPP_)
