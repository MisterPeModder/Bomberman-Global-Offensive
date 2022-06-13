/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Game
*/

#ifndef GAME_GAME_HPP_
#define GAME_GAME_HPP_

#include "ecs/System.hpp"
#include "ecs/World.hpp"
#include "map/Map.hpp"
#include "raylib/core/Camera3D.hpp"
#include "raylib/core/Vector2.hpp"

namespace game
{
    /// Game class
    class Game {
      public:
        /// Game parameters
        struct Parameters {
            /// Number of players (users/AI)
            size_t playerCount;
            /// Number of lives for each player
            size_t livesCount;
            /// Size of the map
            raylib::core::Vector2u mapSize;

            /// Construct a new game Parameters object
            ///
            /// @param pplayerCount @ref playerCount
            /// @param plivesCount @ref livesCount
            /// @param pmapSize @ref mapSize
            Parameters(size_t pplayerCount = 1, size_t plivesCount = 1, raylib::core::Vector2u pmapSize = {13, 13})
                : playerCount(pplayerCount), livesCount(plivesCount), mapSize(pmapSize)
            {
            }
        };

        /// Construct a new Game.
        ///
        /// @param world world in which the game takes place.
        /// @param params parameters if the game.
        Game(ecs::World &world, Parameters params = Parameters());

        /// Destroy the game.
        ~Game() = default;

        /// Get the loaded Map.
        ///
        /// @return const map::Map& loaded map.
        const map::Map &getMap() const;

        /// Setup the world entities.
        void setup();

        /// Setup the camera position.
        ///
        /// @param camera camera to use for drawing purposes.
        void setCamera(raylib::core::Camera3D &camera);

        /// Draw a single frame of the game.
        ///
        /// @param camera camera looking at the map.
        ///
        void drawFrame(const raylib::core::Camera3D &camera);

      private:
        ecs::SystemTag _drawing;
        ecs::SystemTag _handleInputs;
        ecs::SystemTag _update;
        ecs::SystemTag _resolveCollisions;
        ecs::World &_world;
        map::Map _map;
        Parameters _params;
    };
} // namespace game

#endif /* !GAME_HPP_ */
