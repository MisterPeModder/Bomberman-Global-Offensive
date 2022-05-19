/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Base Component
*/

#ifndef ECS_COMPONENT_HPP_
#define ECS_COMPONENT_HPP_

namespace ecs
{
    /// The base component type, all components must inherit from Component.
    class Component {
      public:
        virtual ~Component() = default;
    };
} // namespace ecs

#endif // !defined(ECS_COMPONENT_HPP_)
