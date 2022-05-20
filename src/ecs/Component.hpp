/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Base Component
*/

#ifndef ECS_COMPONENT_HPP_
#define ECS_COMPONENT_HPP_

#include "ecs/storage/Storage.hpp"

namespace ecs
{
    class BaseComponent {
      public:
        virtual ~BaseComponent() = default;

      protected:
        BaseComponent() = default;
    };

    /// The base component type, all components must inherit from Component.
    ///
    /// @tparam S The backing storage type, any of SparseStorage, DenseStorage, or TreeStorage.
    template <Storage S> class Component : public BaseComponent {
      public:
        /// The backing storage type.
        using Storage = S;

        virtual ~Component() = default;

      protected:
        Component() = default;
    };
} // namespace ecs

#endif // !defined(ECS_COMPONENT_HPP_)