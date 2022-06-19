/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** GameClock
*/

#ifndef GAME_COMPONENTS_GAMECLOCK_HPP_
#define GAME_COMPONENTS_GAMECLOCK_HPP_

#include <chrono>
#include "ecs/Component.hpp"
#include "ecs/resource/Resource.hpp"

namespace game::resources
{
    /// Game related clock.
    class GameClock : public ecs::Resource {
      public:
        /// Starts the clock.
        GameClock();

        /// Get the effective time passed in the game.
        std::chrono::milliseconds getTime() const;

        /// Get the time elapsed since the last frame.
        std::chrono::milliseconds elapsed() const;
        /// Get the time elapsed since the last frame (in seconds).
        float elapsedSeconds() const;

        /// Update the internal time. (must be call one time per frame).
        void update();

        /// (Un)pause the clock. When the clock is paused, time stops: elapsed returns 0 and the internal time doesn't
        /// change.
        /// @param pause If the clock must be paused.
        void pause(bool pause = true);

        /// Toggle the pause
        void togglePause();

        /// Check if the clock is paused.
        ///
        /// @retval true if the clock is paused.
        /// @retval false if the clock is running.
        bool isPaused() const;

      private:
        std::chrono::milliseconds _gameTime;
        std::chrono::steady_clock::time_point _lastReset;
        bool _paused;
        std::chrono::nanoseconds _lastFrame;
    };
} // namespace game::resources

#endif /* !GAME_COMPONENTS_GAMECLOCK_HPP_ */
