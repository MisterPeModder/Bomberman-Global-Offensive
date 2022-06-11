/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Living
*/

#ifndef GAME_COMPONENTS_LIVING_HPP_
#define GAME_COMPONENTS_LIVING_HPP_

#include "ecs/Component.hpp"

namespace game::components
{
    /// Living component
    struct Living : public ecs::Component {
        /// Number of health point (hp) left.
        size_t hp;
        /// Number of hp max.
        size_t hpMax;

        /// Construct a new Living component.
        ///
        /// @param pHp @ref hp.
        /// @param pHpMax @ref hpMax;
        Living(size_t pHp, size_t pHpMax) : hp(pHp), hpMax(pHpMax) {}

        /// Construct a new Living component.
        /// @note @c pHp will also be used for @c hpMax.
        ///
        /// @param pHp @ref hp.
        Living(size_t pHp = 1) : hp(pHp), hpMax(pHp) {}
    };
} // namespace game::components

#endif /* !GAME_COMPONENTS_LIVING_HPP_ */
