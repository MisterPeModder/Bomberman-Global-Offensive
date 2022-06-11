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
#include "raylib/core/Vector2.hpp"

namespace game
{
    namespace map
    {
        /// Bomberman Map
        class Map {
          private:
            using Vector2u = raylib::core::Vector2u;

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
            /// @param size size of the map
            Map(Vector2u size = {13, 13});

            /// Destroy the map
            ~Map() = default;

            /// Generate the map.
            ///
            /// @param size size of the map
            /// @throw InvalidMapSize when the size is invalid (< 3 or even)
            void generate(Vector2u size);

            /// Get the Element at the requested position.
            ///
            /// @param position element position
            /// @return Element element at the requested position
            /// @throw std::out_of_bounds when the position is out of the map bounds
            Element getElement(Vector2u position) const;

            /// Get the Element at the requested position.
            ///
            /// @param position element position
            /// @return Element& element at the requested position
            /// @throw std::out_of_bounds when the position is out of the map bounds
            Element &getElement(Vector2u position);

            /// Get the Size of the map.
            ///
            /// @return Vector2u mapSize;
            Vector2u getSize() const;

            /// Get the Player Starting Position based on its id.
            ///
            /// @param playerId player ID.
            /// @return Vector2 starting position of the player in the map.
            Vector2u getPlayerStartingPosition(game::User::UserId playerId);

          private:
            /// Ensure the corners to be empty to avoid invalid player spawn
            void freeCorners();

            Vector2u _size;
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
