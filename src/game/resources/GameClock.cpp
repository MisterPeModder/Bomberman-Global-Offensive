/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GameClock
*/

#include "GameClock.hpp"

namespace game::resources
{
    GameClock::GameClock() : _gameTime(0), _lastReset(std::chrono::steady_clock::now()), _paused(false), _lastFrame(0)
    {
    }

    std::chrono::milliseconds GameClock::getTime() const { return _gameTime; }

    std::chrono::milliseconds GameClock::elapsed() const
    {
        if (_paused)
            return std::chrono::milliseconds::zero();
        return std::chrono::duration_cast<std::chrono::milliseconds>(_lastFrame);
    }

    float GameClock::elapsedSeconds() const
    {
        if (_paused)
            return 0;
        return std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1>>>(_lastFrame).count();
    }

    void GameClock::update()
    {
        if (_paused)
            return;
        _lastFrame = std::chrono::steady_clock::now() - _lastReset;
        _lastReset = std::chrono::steady_clock::now();
        _gameTime += elapsed();
    }
    void GameClock::pause(bool pause)
    {
        if (pause == _paused)
            return;
        if (pause) {
            update();
            _lastFrame = std::chrono::milliseconds(0);
        } else
            _lastReset = std::chrono::steady_clock::now();
        _paused = pause;
    }

} // namespace game::resources
