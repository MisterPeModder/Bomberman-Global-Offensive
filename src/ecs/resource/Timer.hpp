/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Timer World Resource
*/

#ifndef ECS_RESOURCE_TIMER_HPP_
#define ECS_RESOURCE_TIMER_HPP_

#include "ecs/resource/Resource.hpp"

#include <chrono>

/// Entity-Component-System namespace.
namespace ecs
{
    /// Simple timer resource.
    class Timer final : public Resource {
      public:
        /// Creates a new timer.
        explicit Timer() noexcept;

        /// Resets the timer.
        void reset() noexcept;

        /// @returns The seconds since the last call to reset() (or construction of the Timer).
        double elapsed() const noexcept;

      private:
        std::chrono::steady_clock::time_point _lastReset;
    };
} // namespace ecs

#endif // !defined(ECS_RESOURCE_TIMER_HPP_)
