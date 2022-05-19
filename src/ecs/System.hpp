/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Base System
*/

#ifndef ECS_SYSTEM_HPP_
#define ECS_SYSTEM_HPP_

namespace ecs
{
    /// TBD
    class EntityAccess {
    };

    /// The base system type, all systems must inherit from System.
    class System {
      public:
        virtual ~System() = default;

        /// Updates the provided entities.
        virtual void run(EntityAccess &entities) = 0;
    };
} // namespace ecs

#endif // !defined(ECS_SYSTEM_HPP_)
