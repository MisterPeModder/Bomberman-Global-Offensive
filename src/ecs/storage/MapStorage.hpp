/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Map Component Storage
*/

#ifndef ECS_STORAGE_MAP_STORAGE_HPP_
#define ECS_STORAGE_MAP_STORAGE_HPP_

#include "ecs/Entity.hpp"
#include "ecs/storage/Storage.hpp"
#include "util/BitSet.hpp"

#include <map>

namespace ecs
{
    /// Map-based component storage.
    template <typename C> class MapStorage final : public Storage {
      public:
        using Component = C;

        /// Default initialization of MapStorage
        explicit MapStorage() : _mask(0) {}

        /// Cannot copy storage instances.
        MapStorage(MapStorage const &) = delete;

        /// Constructs a component in-place for the given entity.
        ///
        /// @param entity The entity.
        /// @param args The arguments that will be passed to the component's constructor.
        template <typename... Args> void emplace(Entity::Index entity, Args &&...args)
        {
            this->_components.emplace(std::piecewise_construct, std::forward_as_tuple(entity),
                std::forward_as_tuple(std::forward<Args>(args)...));
            this->_mask.resize(std::max(this->_mask.size(), entity + 1));
            this->_mask[entity] = true;
        }

        /// Removes the component instance for the supplied entity.
        void erase(Entity::Index entity)
        {
            this->_components.erase(entity);
            this->_mask[entity] = false;
        }

        /// @returns Whether the entity exists in this storage.
        bool contains(Entity::Index entity) const { return this->_components.contains(entity); }

        /// @returns The component accociated with the given entity.
        /// @throws std::exception if @b entity does not exist in this storage.
        Component &operator[](Entity::Index entity) { return this->_components.at(entity); }

        /// @returns The component accociated with the given entity.
        /// @throws std::exception if @b entity does not exist in this storage.
        Component const &operator[](Entity::Index entity) const { return this->_components.at(entity); }

        /// @returns The amount of entities in this storage.
        std::size_t size() const noexcept { return this->_components.size(); }

        /// Fetches a bit set where each set bit corresponds to an entity that possesses a component of type @b
        /// Component in this storage.
        ///
        /// @return The component mask.
        constexpr util::BitSet const &getMask() const noexcept { return this->_mask; }

      private:
        /// backing map storage.
        std::map<Entity::Index, Component> _components;
        util::BitSet _mask;
    };

    static_assert(IsStorage<MapStorage<std::nullptr_t>>);
} // namespace ecs

#endif //! defined(ECS_STORAGE_MAP_STORAGE_HPP_)
