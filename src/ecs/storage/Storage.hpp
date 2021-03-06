/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - The Component Storage Trait
*/

#ifndef ECS_STORAGE_STORAGE_HPP_
#define ECS_STORAGE_STORAGE_HPP_

#include "ecs/Entity.hpp"
#include "ecs/join/Joinable.hpp"

#include <concepts>
#include <iterator>
#include <span>

// forward declaration of MapStorage for use as default storage type.
namespace ecs
{
    template <typename C> class MapStorage;
}

/// @internal
/// @note Use ecs::get_storage_type instead.
template <typename C> struct GetComponentStorageType {
    using Value = ecs::MapStorage<C>;
};

/// Sets the storage type to use for @b ComponentType, if not called @b MapStorage is used by default.
#define SET_COMPONENT_STORAGE(ComponentType, StorageType)       \
    template <> struct GetComponentStorageType<ComponentType> { \
        using Value = StorageType<ComponentType>;               \
    };

namespace util
{
    class BitSet;
}

namespace ecs
{
    /// used to declare a virtual destructor on all Storage implementations.
    class Storage {
      public:
        virtual ~Storage() = default;

        /// Removes all components belonging to the entities in @b toRemove.
        ///
        /// @param toRemove The set of entities to be removed.
        virtual void maintain(std::span<Entity> toRemove) = 0;
    };

    /// The Compoonent storage trait.
    ///
    /// @note The iterators supplied by storages @b must yield their entity-component pair in increasing order of entity
    /// index.
    template <typename S>
    concept IsStorage = std::default_initializable<S> && std::derived_from<S, Storage> && requires(
        S &storage, S const &cstorage, Entity::Index entity)
    {
        // clang-format off
        typename S::Component;

        // required methods, we cannot test for emplace()
        storage.erase(entity);
        { cstorage.contains(entity) } -> std::same_as<bool>;
        { storage[entity] } -> std::same_as<typename S::Component &>;
        { cstorage[entity] } -> std::same_as<typename S::Component const &>;
        { cstorage.size() } noexcept -> std::same_as<std::size_t>;
        { cstorage.getMask() } noexcept -> std::same_as<util::BitSet const &>;
        // clang-format on
    };

    /// Get the storage type of a component, returns MapStorage by default.
    template <typename C> using getStorageType = typename GetComponentStorageType<C>::Value;

    /// All instances of IsStorage are joinable.
    template <IsStorage Storage> struct JoinTraits<Storage> {
        using Data = typename Storage::Component &;

        static util::BitSet const &getMask(Storage const &storage) { return storage.getMask(); }

        static Data getData(Storage &storage, std::size_t index) { return storage[index]; }
    };
} // namespace ecs

#endif // !defined(ECS_STORAGE_STORAGE_HPP_)
