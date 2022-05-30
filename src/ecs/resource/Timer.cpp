/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - Timer World Resource
*/

#include "ecs/resource/Timer.hpp"

#include <chrono>

/// Entity-Component-System namespace.
namespace ecs
{
    Timer::Timer() noexcept : _lastReset(std::chrono::steady_clock::now()) {}

    void Timer::reset() noexcept { this->_lastReset = std::chrono::steady_clock::now(); }

    double Timer::elapsed() const noexcept
    {
        std::chrono::steady_clock::time_point now(std::chrono::steady_clock::now());
        std::chrono::duration<float, std::ratio<1>> elapsed = now - this->_lastReset;

        return elapsed.count();
    }
} // namespace ecs
