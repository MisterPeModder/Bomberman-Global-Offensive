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

#include <map>

namespace ecs
{
    template <typename C> class MapStorage : public BaseStorage {
      public:
        using Component = C;
        using Iterator = typename std::map<Entity, Component>::iterator;
        using ConstIterator = typename std::map<Entity, Component>::const_iterator;

        /// Default initialization of MapStorage
        explicit MapStorage() {}

        /// Cannot copy storage instances.
        MapStorage(MapStorage const &) = delete;

        /// Constructs a component in-place for the given entity.
        ///
        /// @param entity The entity.
        /// @param args The arguments that will be passed to the component's constructor.
        template <typename... Args> void emplace(Entity entity, Args &&...args)
        {
            this->_components.emplace(std::piecewise_construct, std::forward_as_tuple(entity),
                std::forward_as_tuple(std::forward<Args>(args)...));
        }

        /// Removes the component instance for the supplied entity.
        void erase(Entity entity) { this->_components.erase(entity); }

        /// @returns Whether the entity exists in this storage.
        bool contains(Entity entity) const { return this->_components.contains(entity); }

        /// @returns The component accociated with the given entity.
        /// @throws std::exception if @b entity does not exist in this storage.
        Component &operator[](Entity entity) { return this->_components.at(entity); }

        /// @returns The component accociated with the given entity.
        /// @throws std::exception if @b entity does not exist in this storage.
        Component const &operator[](Entity entity) const { return this->_components.at(entity); }

        /// @returns The amount of entities in this storage.
        std::size_t size() const noexcept { return this->_components.size(); }

        /// Iterator start.
        Iterator begin() noexcept { return this->_components.begin(); }

        /// Constant iterator start.
        ConstIterator cbegin() const noexcept { return this->_components.cbegin(); }

        /// Iterator end.
        Iterator end() noexcept { return this->_components.end(); }

        /// Constant iterator end.
        ConstIterator cend() const noexcept { return this->_components.cend(); }

      private:
        /// backing map storage.
        std::map<Entity, Component> _components;
    };

    static_assert(Storage<MapStorage<std::nullptr_t>>);
} // namespace ecs

#endif //! defined(ECS_STORAGE_MAP_STORAGE_HPP_)
