/*
** EPITECH PROJECT, 2022
** Bomberman: Global Offensive
** File description:
** GAME - AnimTimer World Resource
*/

#ifndef GAME_RESOURCES_ANIMTIMER_HPP_
#define GAME_RESOURCES_ANIMTIMER_HPP_

#include "ecs/resource/Resource.hpp"
#include "ecs/resource/Timer.hpp"

#include <chrono>

/// Entity-Component-System namespace.
namespace game
{
    /// Simple timer resource.
    class AnimTimer final : public ecs::Timer {
    };
} // namespace game

#endif // !defined(GAME_RESOURCES_ANIMTIMER_HPP_)
