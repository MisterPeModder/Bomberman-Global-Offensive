/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#ifndef ECS_WORLD_HPP_
#define ECS_WORLD_HPP_

#include "ecs/Component.hpp"
#include "ecs/Instances.hpp"
#include "ecs/System.hpp"
#include "ecs/storage/Storage.hpp"
#include "ecs/storage/TreeStorage.hpp"
#include "ecs/world/Resource.hpp"

#include <concepts>
#include <stdexcept>
#include <utility>
#include <unordered_map>

namespace ecs
{
    class Entity;

    /// Contains all entities and systems.
    class World {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Instantiation
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        explicit World();

        World(World const &) = delete;

        ~World() = default;

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Populating
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Creates a new entity
        Entity &addEntity();

        /// Adds a new world Resource instance.
        ///
        /// @tparam R The type of resource to instantiate, must be derived from the Resource class.
        /// @tparam Args The type of arguments to pass to the constructor of @b R.
        ///
        /// @param args The arguments to pass to the constructor of @b R.
        ///
        /// @returns A reference to the instance of @b R, lives as long as this world.
        ///
        /// @throws std::logic_error If the resource @b R was already added to this world.
        template <std::derived_from<Resource> R, typename... Args> R &addResource(Args &&...args)
        {
            return this->_resources.emplace<R>(
                "tried to register same resource type twice", std::forward<Args>(args)...);
        }

        /// Creates a instance of the system @b S and adds it the active systems of this World.
        ///
        /// @tparam S The type of system to instantiate, must be derived from the System class.
        /// @tparam Args The type of arguments to pass to the constructor of @b S.
        ///
        /// @param args The arguments to pass to the constructor of @b S.
        ///
        /// @throws std::logic_error If the system @b S was already added to this world.
        template <std::derived_from<System> S, typename... Args> void addSystem(Args &&...args)
        {
            this->_systems.emplace<S>("tried to register same system type twice", std::forward<Args>(args)...);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Runs all systems in this world.
        void runSystems();

        /// Run a specific system, useful if you want to run to time/resource-intensive system separately.
        ///
        /// @throws std::logic_error If the system @b S was not added to this world.
        template <std::derived_from<System> S> void runSystem()
        {
            this->runSystem(this->_systems.get<S>("tried to run unregistered system"));
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Querying
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Fetches a Resource from this world.
        ///
        /// @tparam Value The type of resource to fetch, must inherit from @b Resource.
        ///
        /// @returns A const reference to the instance of @b R.
        ///
        /// @throws std::logic_error If no instance of @b R is in the world.
        template <std::derived_from<Resource> R> R const &getResource() const
        {
            return this->_resources.get<R>(("attempted to access unregistered resource instance"));
        }

        /// Fetches a Resource from this world.
        ///
        /// @tparam R The type of resource to fetch, must inherit from @b Resource.
        ///
        /// @returns A reference to the instance of @b R.
        ///
        /// @throws std::logic_error If no instance of @b R is in the world.
        template <std::derived_from<Resource> R> R &getResource()
        {
            return this->_resources.get<R>(("attempted to access unregistered resource instance"));
        }

        /// Fetches a component storage from this world.
        ///
        /// @tparam C The component type.
        ///
        /// @returns A const reference to the storage of components of type @b C.
        ///
        /// @throws std::logic_error If no storage for component @b C exists.
        template <std::derived_from<Component> C> get_storage_type<C> const &getStorage() const
        {
            return this->_storages.get<get_storage_type<C>>("attempted to access unregistered storage");
        }

        /// Fetches a component storage from this world.
        ///
        /// @tparam C The component type.
        ///
        /// @returns A reference to the storage of components of type @b C.
        ///
        /// @throws std::logic_error If no storage for component @b C exists.
        template <std::derived_from<Component> C> get_storage_type<C> &getStorage()
        {
            return this->_storages.get<get_storage_type<C>>("attempted to access unregistered storage");
        }

      private:
        Instances<Resource> _resources;
        Instances<System> _systems;
        Instances<BaseStorage> _storages;

        /// non template version of runSystem.
        void runSystem(System &system);
    };
} // namespace ecs

#endif // !defined(ECS_WORLD_HPP_)
