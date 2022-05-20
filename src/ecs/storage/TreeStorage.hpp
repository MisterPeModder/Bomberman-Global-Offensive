/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Tree Component Storage
*/

#ifndef ECS_STORAGE_TREE_STORAGE_HPP_
#define ECS_STORAGE_TREE_STORAGE_HPP_

#include "ecs/Entity.hpp"
#include "ecs/storage/Storage.hpp"

#include <map>

namespace ecs
{
    template <typename C> class TreeStorage : public BaseStorage {
      public:
        using Component = C;
        using Iterator = std::map<Entity, Component>::iterator;
        using ConstIterator = std::map<Entity, Component>::const_iterator;

        /// Default initialization of TreeStorage
        explicit TreeStorage() {}

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

    static_assert(Storage<TreeStorage<std::nullptr_t>>);
} // namespace ecs

#endif //! defined(ECS_STORAGE_TREE_STORAGE_HPP_)
