/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GameClock
*/

#include "GameClock.hpp"

namespace game::resources
{
    GameClock::GameClock() : _gameTime(0), _lastReset(std::chrono::steady_clock::now()), _paused(false) {}

    std::chrono::milliseconds GameClock::getTime() const { return _gameTime; }

    std::chrono::milliseconds GameClock::elapsed() const
    {
        if (_paused)
            return std::chrono::milliseconds::zero();
        return std::chrono::steady_clock::now() - _lastReset;
    }

    void GameClock::update()
    {
        if (_paused)
            return;
        _gameTime += elapsed();
        _lastReset = std::chrono::steady_clock::now();
    }
    void GameClock::pause(bool pause = true)
    {
        if (pause == _paused)
            return;
        if (pause)
            update();
        else
            _lastReset = std::chrono::steady_clock::now();
        _paused = pause;
    }

} // namespace game::resources
