/*
** EPITECH PROJECT, 2022
** BMGO
** File description:
** Reference
*/

#ifndef GAME_COMPONENTS_REFERENCE_HPP_
#define GAME_COMPONENTS_REFERENCE_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    /// Templated Reference component.
    /// @tparam T type of the object wrapped.
    template <typename T> struct Reference : public ecs::Component {
        T &object;

        Reference(const T &pObject) : object(pObject) {}
    };
} // namespace game::components

#endif
