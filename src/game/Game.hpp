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
        /// @param params parameters if the game.
        Game(Parameters params = Parameters());

        /// Destroy the game.
        ~Game() = default;

        /// Get the loaded Map.
        ///
        /// @return const map::Map& loaded map.
        const map::Map &getMap() const;

        /// @returns A constant reference to the game's camera.
        raylib::core::Camera3D const &getCamera() const;

        /// @returns A reference to the game's camera.
        raylib::core::Camera3D &getCamera();

        /// Set the active gamera.
        ///
        /// @param camera The camera.
        void setCamera(raylib::core::Camera3D &&camera);

        /// Setup the world entities and the camera position.
        void setup();

        /// Draw a single frame of the game.
        void drawFrame();

        /// Start of the main event loop.
        void run();

      private:
        ecs::SystemTag _drawing;
        ecs::SystemTag _handleInputs;
        ecs::SystemTag _update;
        ecs::SystemTag _resolveCollisions;
        ecs::World _world;
        map::Map _map;
        Parameters _params;
        raylib::core::Camera3D _camera;
    };
} // namespace game

#endif /* !GAME_HPP_ */
