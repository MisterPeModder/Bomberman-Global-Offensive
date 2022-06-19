/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** ECS - GameTimer World Resource
*/

#ifndef ECS_RESOURCE_GAMETIMER_HPP_
#define ECS_RESOURCE_GAMETIMER_HPP_

#include "ecs/resource/Resource.hpp"
#include "ecs/resource/Timer.hpp"

#include <chrono>

/// Entity-Component-System namespace.
namespace game
{
    /// Simple timer resource.
    class GameTimer final : public ecs::Timer {};
} // namespace game

#endif // !defined(ECS_RESOURCE_GAMETIMER_HPP_)
