/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Marker Component "Storage"
*/

#ifndef ECS_STORAGE_MARKER_STORAGE_HPP_
#define ECS_STORAGE_MARKER_STORAGE_HPP_

#include "ecs/Entity.hpp"
#include "ecs/storage/Storage.hpp"
#include "util/BitSet.hpp"

#include <concepts>

namespace ecs
{
    /// "Storage" for marker-like components, does not store any data except for which entities have the marker.
    ///
    /// @tparam C The component type, must be default-constructible.
    template <std::default_initializable C> class MarkerStorage final : public Storage {
      public:
        using Component = C;

        /// Default initialization of MarkerStorage
        explicit MarkerStorage() : _size(0), _mask(0), _instance() {}

        /// Marks the given entity
        ///
        /// @param entity The entity.
        template <typename... Args> void emplace(Entity::Index entity)
        {
            this->_mask.resize(std::max(this->_mask.size(), entity + 1));
            this->_mask[entity] = true;
            ++this->_size;
        }

        /// Removes the component instance for the supplied entity.
        constexpr void erase(Entity::Index entity)
        {
            this->_mask[entity] = false;
            --this->_size;
        }

        /// @returns Whether the entity exists in this storage.
        BIT_SET_CONSTEXPR bool contains(Entity::Index entity) const
        {
            return entity < this->_size && this->_mask[entity];
        }

        /// @returns The component instance.
        constexpr Component &operator[](Entity::Index) { return this->_instance; }

        /// @returns The component instance.
        constexpr Component const &operator[](Entity::Index) const { return this->_instance; }

        /// @returns The amount of marked entities.
        constexpr std::size_t size() const noexcept { return this->_size; }

        /// Fetches a bit set where each set bit corresponds to an entity that possesses a component of type @b
        /// Component in this storage.
        ///
        /// @return The component mask.
        constexpr util::BitSet const &getMask() const noexcept { return this->_mask; }

      private:
        std::size_t _size;
        util::BitSet _mask;
        Component _instance;
    };

    static_assert(IsStorage<MarkerStorage<int>>);
} // namespace ecs

#endif //! defined(ECS_STORAGE_MARKER_STORAGE_HPP_)
