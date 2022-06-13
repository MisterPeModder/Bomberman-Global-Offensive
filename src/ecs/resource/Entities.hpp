/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Entity Resource
*/

#ifndef ECS_RESOURCE_ENTITIES_HPP_
#define ECS_RESOURCE_ENTITIES_HPP_

#include "ecs/Component.hpp"
#include "ecs/Entity.hpp"
#include "ecs/join/Joinable.hpp"
#include "ecs/resource/Resource.hpp"
#include "ecs/storage/Storage.hpp"
#include "util/BitSet.hpp"

#include <concepts>
#include <vector>

namespace ecs
{
    /// The entities world resource.
    class Entities final : public Resource {
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
            [[nodiscard]] Builder &with(getStorageType<C> &storage, Args &&...args)
            {
                this->checkConsumed();
                if (storage.contains(this->_entity.getId()))
                    throw std::logic_error("attempted to add same component to an entity twice");
                storage.emplace(this->_entity.getId(), std::forward<Args>(args)...);
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

        /// Marks an entity for deletion on the next call to @ref Entities::maintain().
        ///
        /// @returns @b true if the entity was successfully marked.
        bool kill(Entity entity) noexcept;

        /// Returns an entity with a given @b id.
        /// There's no guarantee for validity, meaning the entity could be not alive.
        ///
        /// @param id The entity's index.
        ///
        /// @return The entity's handle.
        Entity get(Entity::Index id) noexcept;

        /// @returns Whether the entity is alive.
        bool isAlive(Entity entity) noexcept;

        /// Removes all entities marked for deletion. Prefer @ref World::maintain() over this when possible.
        ///
        /// @note Invalidates @b ALL iterators!
        ///
        /// @returns A vector of all the deleted entities.
        std::vector<Entity> maintain();

      private:
        std::vector<Entity::Generation> _generations;
        util::BitSet _alive;
        util::BitSet _killed;

        Entity create(bool alive);

        // Allow Entities::Builder to access Entities internals.
        friend Builder;
        friend struct JoinTraits<Entities>;
    };

    /// Joinable implementation for the Entities resource.
    template <> struct JoinTraits<Entities> {
        using Data = Entity;

        static constexpr util::BitSet const &getMask(Entities const &entities) { return entities._alive; }

        static Data getData(Entities &entities, std::size_t index) { return entities.get(index); }
    };
    static_assert(Joinable<Entities>);
} // namespace ecs

#endif // !defined(ECS_RESOURCE_ENTITIES_HPP_)
