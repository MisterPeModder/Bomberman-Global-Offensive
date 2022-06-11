/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#ifndef ECS_WORLD_WORLD_HPP_
#define ECS_WORLD_WORLD_HPP_

#include "ecs/Component.hpp"
#include "ecs/resource/Entities.hpp"
#include "ecs/resource/Resource.hpp"
#include "ecs/storage/Storage.hpp"
#include "ecs/system/System.hpp"
#include "ecs/world/Instances.hpp"

#include <concepts>
#include <stdexcept>
#include <utility>
#include <unordered_map>

namespace ecs
{
    class Entity;
    class System;

    /// Contains all entities and systems.
    class World final {
      public:
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Instantiation
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ECS World Instantiation

        explicit World();

        World(World const &) = delete;

        ~World() = default;

#pragma endregion ECS World Instantiation
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Populating
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ECS World Populating

        /// Allows one to construct an entity component by component.
        class EntityBuilder {
          public:
            /// Cannot copy entity builders.
            EntityBuilder(EntityBuilder const &) = delete;

            /// Attach a component to the entity.
            ///
            /// @tparam C The component to attach, must not already exist on the entity.
            /// @tparam Args The type of arguments to pass to the constructor of @b C.
            ///
            /// @param args The arguments to pass to the constructor of @b C.
            ///
            /// @throws std::logic_error if @b C is already present on the entity,
            /// or if this method is called after build().
            template <std::derived_from<Component> C, typename... Args>
            [[nodiscard]] EntityBuilder &with(Args &&...args)
            {
                if (!this->_outer._storages.contains<getStorageType<C>>())
                    this->_outer._storages.emplace<getStorageType<C>>("failed to add entity component");
                static_cast<void>(this->_builder.with<C>(this->_outer.getStorage<C>(), std::forward<Args>(args)...));
                return *this;
            }

            /// Creates the entity, consuming the builder.
            ///
            /// @returns The newly created entity's handle.
            ///
            /// @throws std::logic_error If this method is called again.
            Entity build();

          private:
            World &_outer;
            Entities::Builder _builder;

            explicit EntityBuilder(World &outer);

            // Only World may create instances of EntityBuilder.
            friend World;
        };

        /// Creates a new entity
        [[nodiscard]] EntityBuilder addEntity();

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

        /// Registers a component's storage.
        ///
        /// Normally, component storages are auto-registered when the @ref EntityBuilder::with() method is called.
        /// But you wouldn't be able to use @ref ecs::maybe() with a Component that is not used by any entity in the
        /// world.
        ///
        /// Use this function when you want to perform optional joins with the component @b C that might not be present
        /// in the current entities.
        ///
        /// @tparam C The component type to register.
        ///
        /// @returns A reference to the Component's storage.
        template <std::derived_from<Component> C> getStorageType<C> &addStorage()
        {
            if (!this->_storages.contains<getStorageType<C>>())
                return this->_storages.emplace<getStorageType<C>>("failed to add entity component");
            return this->_storages.get<getStorageType<C>>("failed to fetch storage");
        }

#pragma endregion ECS World Populating
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Running
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ECS World Running

        /// Runs all systems in this world.
        void runSystems();

        /// Run a specific system, useful if you want to run to time/resource-intensive system separately.
        ///
        /// @throws std::logic_error If the system @b S was not added to this world.
        template <std::derived_from<System> S> void runSystem()
        {
            this->runSystem(this->_systems.get<S>("tried to run unregistered system"));
        }

#pragma endregion ECS World Running
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Querying
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma region ECS World Querying

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
        template <std::derived_from<Component> C> getStorageType<C> const &getStorage() const
        {
            return this->_storages.get<getStorageType<C>>("attempted to access unregistered storage");
        }

        /// Fetches a component storage from this world.
        ///
        /// @tparam C The component type.
        ///
        /// @returns A reference to the storage of components of type @b C.
        ///
        /// @throws std::logic_error If no storage for component @b C exists.
        template <std::derived_from<Component> C> getStorageType<C> &getStorage()
        {
            return this->_storages.get<getStorageType<C>>("attempted to access unregistered storage");
        }

#pragma endregion ECS World Querying
      private:
        Instances<Resource> _resources;
        Instances<System> _systems;
        Instances<Storage> _storages;

        /// non template version of runSystem.
        void runSystem(System &system);

        // Allow EntityBuilder to access World internals.
        friend EntityBuilder;
    };
} // namespace ecs

#endif // !defined(ECS_WORLD_WORLD_HPP_)
