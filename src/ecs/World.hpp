/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - World
*/

#ifndef ECS_WORLD_HPP_
#define ECS_WORLD_HPP_

#include "System.hpp"

#include <concepts>
#include <memory>
#include <stdexcept>
#include <typeindex>
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

        explicit World(World const &);

        /// Implicit copy of World instances is disabled for performance reasons.
        World &operator=(World const &) = delete;

        ~World();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Populating
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Creates a new entity
        Entity &addEntity();

        /// Creates a instance of the system @b S and adds it the active systems of this World.
        ///
        /// @tparam S The type of system to instantiate, must be derived from the System class.
        /// @tparam Args The type of arguments to pass to the constructor of @b S.
        ///
        /// @param args The arguments to pass to the constructor of @b S.
        ///
        /// @returns A reference to the instance of @b S, lives as long as this world.
        ///
        /// @throws std::logic_error If the system @b S was already added to this world.
        template <std::derived_from<System> S, typename... Args> S &addSystem(Args &&...args)
        {
            std::type_index key(typeid(S));

            if (this->_tmpSystems.contains(key))
                throw std::logic_error("tried to register same system type twice");

            std::unique_ptr<S> instance(std::make_unique<S, Args...>(std::forward<Args>(args)...));
            S *instancePtr(instance.get());

            this->_tmpSystems.emplace(std::make_pair(std::type_index(typeid(S)), std::move(instance)));
            return *instancePtr;
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
            S *system(this->getSystemPtr<S>("tried to run unregistered system"));
            EntityAccess tmpAccess; // TO REMOVE

            system->run(tmpAccess);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Misc
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <std::derived_from<System> S> S const &getSystem() const
        {
            return *this->getSystemPtr<S>("attempted to access unregietered system instance");
        }

        template <std::derived_from<System> S> S &getSystem()
        {
            return *this->getSystemPtr<S>("attempted to access unregietered system instance");
        }

      private:
        std::unordered_map<std::type_index, std::unique_ptr<System>> _tmpSystems;

        /// @returns
        template <std::derived_from<System> S> S *getSystemPtr(const char *error) const
        {
            auto found = this->_tmpSystems.find(std::type_index(typeid(S)));

            if (found == this->_tmpSystems.end())
                throw std::logic_error(error);
            return dynamic_cast<S *>(found->second.get());
        }
    };
} // namespace ecs

#endif // !defined(ECS_WORLD_HPP_)
