/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Data passed to systems
*/

#ifndef ECS_SYSTEM_SYSTEM_DATA_HPP_
#define ECS_SYSTEM_SYSTEM_DATA_HPP_

#include "ecs/storage/Storage.hpp"
#include "ecs/world/World.hpp"

#include <concepts>

namespace ecs
{
    class Resource;
    class Component;

    /// A view on world data that provides access to Resource and Storage instances to systems.
    class SystemData final {
      public:
        /// Fetches a Resource from the attached world.
        ///
        /// @tparam Value The type of resource to fetch, must inherit from @b Resource.
        ///
        /// @returns A reference to the instance of @b R.
        ///
        /// @throws std::logic_error If no instance of @b R is in the world.
        template <std::derived_from<Resource> R> R &getResource() const { return this->_world.getResource<R>(); }

        /// Fetches a component storage from the attached world.
        ///
        /// @tparam C The component type.
        ///
        /// @returns A reference to the storage of components of type @b C.
        ///
        /// @throws std::logic_error If no storage for component @b C exists.
        template <std::derived_from<Component> C> getStorageType<C> &getStorage() const
        {
            return this->_world.getStorage<C>();
        }

        explicit SystemData(World &world) : _world(world){};

      private:
        World &_world;

        // only World may create instances of SystemData.
        friend World;
    };
} // namespace ecs

#endif // !defined(ECS_SYSTEM_SYSTEM_DATA_HPP_)
