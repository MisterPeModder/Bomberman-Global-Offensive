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

namespace game::resources
{
    class GameClock : public ecs::Resource {
      public:
        GameClock();

        std::chrono::milliseconds getTime() const;

        std::chrono::milliseconds elapsed() const;
        void update();
        void pause(bool pause = true);

      private:
        std::chrono::milliseconds _gameTime;
        std::chrono::steady_clock::time_point _lastReset;
        bool _paused;
    };
} // namespace game::resources

#endif /* !GAME_COMPONENTS_GAMECLOCK_HPP_ */
