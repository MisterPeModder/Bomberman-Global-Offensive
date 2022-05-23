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

// forward declaration of TreeStorage for use as default storage type.
namespace ecs
{
    template <typename C> class TreeStorage;
}

/// @note Use ecs::get_storage_type instead.
template <typename C> struct GetComponentStorageType {
    using Value = ecs::TreeStorage<C>;
};

/// Sets the storage type to use for @b ComponentType, if not called @b TreeStorage is used by default.
#define SET_COMPONENT_STORAGE(ComponentType, StorageType)       \
    template <> struct GetComponentStorageType<ComponentType> { \
        using Value = StorageType<ComponentType>;               \
    };

namespace ecs
{
    /// used to declare a virtual destructor on all Storage implementations.
    class BaseStorage {
      public:
        virtual ~BaseStorage() = default;
    };

    /// The Compoonent storage trait.
    ///
    /// @note The iterators supplied by storages @b must yield their entity-component pair in increasing order of entity
    /// index.
    template <typename S>
    concept Storage = std::default_initializable<S> && std::derived_from<S, BaseStorage> && requires(
        S &storage, S const &cstorage, Entity entity)
    {
        // clang-format off
        typename S::Component;
        typename S::Iterator;
        typename S::ConstIterator;

        // required methods, we cannot test for emplace()
        storage.erase(entity);
        { cstorage.contains(entity) } -> std::same_as<bool>;
        { storage[entity] } -> std::same_as<typename S::Component &>;
        { cstorage[entity] } -> std::same_as<typename S::Component const &>;

        // the iterators must have a value type of pair<Entity, Component>
        requires std::same_as<typename S::Iterator::value_type, std::pair<const Entity, typename S::Component>>;
        requires std::same_as<typename S::ConstIterator::value_type, std::pair<const Entity, typename S::Component>>;

        // the iterators must satisfy `LegacyForwardIterator`.
        requires std::forward_iterator<typename S::Iterator>;
        requires std::forward_iterator<typename S::ConstIterator>;

        { storage.begin() } noexcept -> std::same_as<typename S::Iterator>;
        { cstorage.cbegin() } noexcept -> std::same_as<typename S::ConstIterator>;

        { storage.end() } noexcept -> std::same_as<typename S::Iterator>;
        { cstorage.cend() } noexcept -> std::same_as<typename S::ConstIterator>;
        // clang-format on
    };

    /// Get the storage type of a component, returns TreeStorage by default.
    template <typename C> using get_storage_type = typename GetComponentStorageType<C>::Value;
} // namespace ecs

#endif // !defined(ECS_STORAGE_HPP_)
