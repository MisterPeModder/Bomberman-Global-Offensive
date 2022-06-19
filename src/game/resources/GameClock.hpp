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
    class GameClock : public ecs::Resource {
      public:
        GameClock();

        std::chrono::milliseconds getTime() const;

        std::chrono::milliseconds elapsed() const;
        float elapsedSeconds() const;

        void update();
        void pause(bool pause = true);
        void togglePause();

        bool isPaused() const;

      private:
        std::chrono::milliseconds _gameTime;
        std::chrono::steady_clock::time_point _lastReset;
        bool _paused;
        std::chrono::nanoseconds _lastFrame;
    };
} // namespace game::resources

#endif /* !GAME_COMPONENTS_GAMECLOCK_HPP_ */
