/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Base System
*/

#ifndef ECS_SYSTEM_SYSTEM_HPP_
#define ECS_SYSTEM_SYSTEM_HPP_

#include <concepts>

namespace ecs
{
    class SystemData;

    /// The base system type, all systems must inherit from System.
    class System {
      public:
        virtual ~System() = default;

        /// Run the system.
        virtual void run(SystemData data) = 0;
    };
} // namespace ecs

#endif // !defined(ECS_SYSTEM_SYSTEM_HPP_)
