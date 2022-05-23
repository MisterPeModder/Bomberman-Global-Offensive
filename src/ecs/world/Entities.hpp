/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Entity Resource
*/

#ifndef ECS_ENTITIES_HPP_
#define ECS_ENTITIES_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/storage/Storage.hpp"
#include "ecs/world/Resource.hpp"

#include <concepts>
#include <vector>

namespace ecs
{
    /// The entities world resource.
    class Entities : public Resource {
      public:
        /// Allows one to construct an entity component by component.
        class Builder {
          public:
            /// Cannot copy entity builders.
            Builder(Builder const &) = delete;

            /// Attach a component to the entity.
            ///
            /// @tparam C The component to attach, must not already exist on the entity.
            /// @tparam Args The type of arguments to pass to the constructor of @b C.
            ///
            /// @param storage The component storage.
            /// @param args The arguments to pass to the constructor of @b C.
            ///
            /// @throws std::logic_error if @b C is already present on the entity,
            /// or if this method is called after build().
            template <std::derived_from<Component> C, typename... Args>
            Builder &with(get_storage_type<C> &storage, Args &&...args)
            {
                this->checkConsumed();
                if (storage.contains(this->_entity))
                    throw std::logic_error("attempted to add same component to an entity twice");
                storage.emplace(this->_entity, std::forward<Args>(args)...);
                return *this;
            }

            /// Creates the entity, consuming the builder.
            ///
            /// @returns The newly created entity's handle.
            ///
            /// @throws std::logic_error If this method is called again.
            Entity build();

          private:
            Entities &_outer;
            Entity _entity;
            bool _consumed;

            Builder(Entities &outer);

            /// @throws std::logic_error If _consumed is @b true.
            void checkConsumed();

            // Only Entities may create instances of Entity::Builder.
            friend Entities;
        };

        explicit Entities();

        /// Creates an empty entity with no components.
        ///
        /// @returns The newly created entity's handle.
        Entity create();

        /// Creates an entity component by component.
        ///
        /// @return The entity's builder.
        [[nodiscard]] Builder builder();

        /// Removes an entity.
        ///
        /// @returns @b true if the entity was successfully removed.
        bool erase(Entity entity) noexcept;

        /// Returns an entity with a given @b id.
        /// There's no guarantee for validity, meaning the entity could be not alive.
        ///
        /// @param id The entity's index.
        ///
        /// @return The entity's handle.
        Entity get(Entity::Index id) noexcept;

        /// @returns Whether the entity is alive.
        bool isAlive(Entity entity) noexcept;

      private:
        std::vector<Entity::Generation> _generations;
        std::vector<bool> _alive;

        Entity create(bool alive);

        // Allow Entities::Builder to access Entities internals.
        friend Builder;
    };
} // namespace ecs

#endif // !defined(ECS_ENTITIES_HPP_)
