/*
** EPITECH PROJECT, 2022
** Bomberman
** File description:
** Map
*/

#ifndef GAME_MAP_HPP_
#define GAME_MAP_HPP_

#include <ostream>
#include <stdexcept>
#include <vector>
#include "game/User.hpp"

namespace game
{
    namespace map
    {
        /// Bomberman Map
        class Map {
          public:
            /// Exception thrown when the map size is invalid.
            class InvalidMapSize : public std::logic_error {
              public:
                /// Construct a new InvalidMapSize object
                ///
                /// @param message what message.
                InvalidMapSize(std::string_view message);
            };

            /// Map element
            enum class Element {
                Wall,  /// Indestructible wall
                Crate, /// Destructible crate
                Empty, /// Nothing
            };

            /// Construct a new Map
            ///
            /// @param width width of the map
            /// @param height height of the map
            Map(size_t width = 13, size_t height = 13);

            /// Destroy the map
            ~Map() = default;

            /// Generate the map.
            ///
            /// @param width width of the map
            /// @param height height of the map
            /// @throw InvalidMapSize when the size is invalid (< 3 or even)
            void generate(size_t width, size_t height);

            /// Get the Element at the position (x, y)
            ///
            /// @param x x position
            /// @param y y position
            /// @return Element element at the position (x, y)
            /// @throw std::out_of_bounds when the position is out of the map bounds
            Element getElement(size_t x, size_t y) const;

            /// Get the Element at the position (x, y)
            ///
            /// @param x x position
            /// @param y y position
            /// @return Element& element at the position (x, y)
            /// @throw std::out_of_bounds when the position is out of the map bounds
            Element &getElement(size_t x, size_t y);

            /// Get the Width of the map
            ///
            /// @return size_t width
            size_t getWidth() const;

            /// Get the height of the map
            ///
            /// @return size_t height
            size_t getHeight() const;

            /// Get the Player Starting Position based on its id.
            ///
            /// @param playerId player ID.
            /// @return Vector2 starting position of the player in the map.
            Vector2 getPlayerStartingPosition(game::User::UserId playerId);

          private:
            /// Ensure the corners to be empty to avoid invalid player spawn
            void freeCorners();

            size_t _width;
            size_t _height;
            std::vector<Element> _map;
        };
    } // namespace map
} // namespace game

/// Output stream operator overload to allow displaying the map.
///
/// @param stream output stream.
/// @param map map to output in the stream (used for debug in @ref std::cout)
/// @return std::ostream& output stream modified.
std::ostream &operator<<(std::ostream &stream, const game::map::Map &map);

#endif /* !GAME_MAP_HPP_ */
